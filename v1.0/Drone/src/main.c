/*
 * Program: main.c
 * Version: Drone Open Beta 1.0
 *
 * Copyright (C) 2013 EVO CONTROLLERS, LLC.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include <string.h>
#include "debug.h"
#include "usb.h"
#include "bluetooth.h"
#include "RGB_LED.h"
#include "analog.h"
#include "drone_game_configurations.h"
#include "systick.h"
#include "buttons.h"
#include "joysticks.h"
#include "configurations/keyboard.h"
#include "configurations/keyboard_IOS.h"
#include "configurations/usb_serial.h"
#include "configurations/keyboard_mouse.h"
#include "configurations/j_stick.h"
#include "configurations/gamepad.h"
#include "system_time.h"
#include "comm.h"
#include "watchdog.h"
#include "ManufactureValidation.h"
#include "battery_charger.h"
#include "powerControl.h"
#include "bios.h"

#define STRINGIFY(x) #x
#define STRINGIFY_EXPANDED(x) STRINGIFY(x)

#define STARTUP_HOLD_TIME_MS 2000
#define STARTUP_DEBOUNCE     10

#define BUTTON_SAMPLE_TIMEOUT_MS 1
#define JOYSTICK_SAMPLE_TIMEOUT_MS 4
#define DEBUG_REPORT_TIMEOUT_MS 1000
#define BATTERY_CHECK_TIMEOUT_MS 1000
#define POWER_OFF_UNUSED_MS 300000
#define STARTUP_HOLD_TIME_MS 2000

// Globals:
struct ControllerConfiguration ccc; // Current Controller Configuration.
struct GlobalHeader global_header;  // The current global header.

// Constants:
const BATTERY_LOW_THRESHOLD = 3500;
const BATTERY_HIGH_THRESHOLD = 4000;

// Locals:
void sysTickCallback(void);    // Callback for the system timer tick.
void selectHandlers(void);     // Selects the correct button and joystick handlers
                               // based off the controller configuration.

void SetupStartPinExternalInterrupt(void);
void maintainControllerStatus(bool pulse);

static ButtonHandlerInit button_handler_init = NULL;
static ButtonHandler button_handler = NULL;
static JoystickHandler joystick_handler = NULL;

// Declarations:
bool pulse, bios, turnedOn;

int main (void)
{
	struct Timeout buttonSampleTimeout;
	struct Timeout joystickSampleTimeout;
	struct Timeout powerOffTimeout;
	struct Timeout biosModeTimeout;
	struct Timeout debugReportTimeout;
	struct Timeout batteryCheckTimeout;
	struct Timeout powerOffUnused; 
	uint8_t i; // temporary variable.
	bool possiblyPoweringOff = false;
	bool possiblyBiosMode = false;
	cfgsel_t which_cfg;
	pulse = false;
	
#if (DEBUG == 1)
	char debugTmpString[40];
#endif
	
	sysclk_init(); //Initialize System Clock
	board_init(); //Setup IO
	delay_ms(5);
	
	setupLEDs(false);
	setLEDValue(0, 0, 1);
	while(buttonActivated(B_START));
	
	btFirstRun();
	turnBTOn(); // Enable the Bluetooth module
	setupBluetoothFast(); // Set baud rate to 115200
	 
	// Post PCB Validation Tests
	if (IsTestMode()) ExecuteTest();
	
	// Setup the watchdog timer period:
	WatchdogInit();

	// Setup the system tick:
	setupSysTick(&sysTickCallback);
	
	// Insert application code here, after the board has been initialized.
	// Setup other peripherals:
	setupDbg();
	setupUsb();
	setupAnalog();	
	enableAnalog();	
	
	// Sample each of the joysticks to set the center values:
	for (i = 0 ; i < NUM_JOYSTICKS; i++) {
		joysticks[i].previous_x = joysticks[i].center_x = joysticks[i].current_x  = sampleAnalogChannel(joysticks[i].adc_channel_x);
		joysticks[i].previous_y = joysticks[i].center_y = joysticks[i].current_y  = sampleAnalogChannel(joysticks[i].adc_channel_y);
	}	
	
	sleepmgr_init(); // Initialize Sleep Manager
	enableSysTick(); // Enable System clock	
	
	SetupStartPinExternalInterrupt();
	
	#if !DEBUG
	pmic_init(); // Enable low/mid/high level interrupts
	cpu_irq_enable(); // Global interrupt enable
	#endif
	
	turnedOn = powerOn(global_header.powerOffSoftware);
	
	// Set the global/controller configuration:
	which_cfg = whichConfiguration();
	loadConfiguration(which_cfg);
	
	selectHandlers();
	setupLEDs(!global_header.led_G_D0_B_D1);

	// Send startup message:
	sendUSBLine("");
	sendUSBLine("+=======+");
	sendUSBLine("| DRONE | Version " STRINGIFY_EXPANDED(SW_VERSION));
	sendUSBLine("+=======+");
	sendDBGLine("");
	sendDBGLine("+=======+");
	sendDBGLine("| DRONE | Version " STRINGIFY_EXPANDED(SW_VERSION));
	sendDBGLine("+=======+");
	
	initBTComms(global_header.bluetooth_mode_names[ccc.mode]);
	
	// Initialize the button handler:
	wdt_reset();
	if (button_handler_init != NULL) {
		button_handler_init(&ccc);
	}
	else
	{
		sendDBGLine("!button_handler_init == null!");
	}		

	// Start the timeouts:
	startTimeout(&buttonSampleTimeout, BUTTON_SAMPLE_TIMEOUT_MS);
	WatchdogPet();
	
	startTimeout(&joystickSampleTimeout, JOYSTICK_SAMPLE_TIMEOUT_MS);
	WatchdogPet();
	
	startTimeout(&debugReportTimeout, DEBUG_REPORT_TIMEOUT_MS);
	WatchdogPet();
	
	startTimeout(&batteryCheckTimeout, BATTERY_CHECK_TIMEOUT_MS);
	WatchdogPet();
	
	startTimeout(&powerOffUnused, POWER_OFF_UNUSED_MS);
	WatchdogPet();
	
	// Except the poweroff timeout:
	cancelTimeout(&powerOffTimeout);
	
	// Main loop:
	sendDBGLine("Entering Main loop");
	while(1) {
		// Go to sleep if there aren't any pending timeouts; wait for the systick to wake us.
		if (!checkTimeout(&buttonSampleTimeout) && !checkTimeout(&joystickSampleTimeout) && !checkTimeout(&batteryCheckTimeout)) {
			sleepmgr_sleep(SLEEPMGR_IDLE);	
		}		
		
		// Pet the WDT:
		WatchdogPet();
		WatchdogTaskRunning(TASK_MAIN);
		
		if (checkTimeout(&batteryCheckTimeout)) {
			startTimeout(&batteryCheckTimeout, BATTERY_CHECK_TIMEOUT_MS);
			
			//Change the pulse state:
			pulse = !pulse;
			
			//Time to check the controller status?
			maintainControllerStatus(pulse);			
		}
		
		// Is it time to sample the buttons?
		if (checkTimeout(&buttonSampleTimeout)) {
			startTimeout(&buttonSampleTimeout, BUTTON_SAMPLE_TIMEOUT_MS);
			
			// Scan the current state of each button:
			for (i = 0; i < NUM_BUTTONS; i++) {
				// Is the button currently released, but being pressed?
				if ((buttons[i].state == BUTTON_RELEASED) && buttonActivated((enum ButtonName)i)) {
					// Then increment the debounce counter:
					buttons[i].debounce_counter++;
				}
				// Or is the button currently pressed, but being released?
				else if ((buttons[i].state != BUTTON_RELEASED) && !buttonActivated((enum ButtonName)i)) {
					// Then increment the debounce counter:
					buttons[i].debounce_counter++;
				}
				// Otherwise reset the debounce counter:
				else {
					buttons[i].debounce_counter = 0;
				}
			}
			
			// Handle button state changes:
			for (i = 0; i < NUM_BUTTONS; i++) {
				// Is the debounce counter pass its threshold?
				if (buttons[i].debounce_counter >= DEBOUNCE_PERIOD) {
					// Then we need to send a press/release event.
					
					// Clear the debounce counter:
					buttons[i].debounce_counter = 0;

					// Is the button's state currently released?
					if (buttons[i].state == BUTTON_RELEASED) {
						// Then it needs to change to pressed:
						buttons[i].state = BUTTON_PRESSED;
					}
					else {
						// Otherwise it needs to change to release:
						buttons[i].state = BUTTON_RELEASED;
					}
					
					// At this point the button has just changed states.
					// Time to notify the device/computer.
					if (button_handler != NULL) {
						startTimeout(&powerOffUnused, POWER_OFF_UNUSED_MS);
						button_handler((enum ButtonName)i, buttons[i].state);
					}
					
					//Only send 1 B_START pressed message for the press event, 
					//  and filter all subsequent pressed messages until released
					if( B_START==i && buttons[B_START].state == BUTTON_PRESSED)
					{
						buttons[B_START].state = BUTTON_LONG_PRESS;
						button_handler( B_START, BUTTON_RELEASED );  //send message with B_START released
					}
				}
			}
			
			// Start the power off timeout if the start button was just pressed:
			if (!possiblyPoweringOff && buttons[B_START].state != BUTTON_RELEASED ) {
				possiblyPoweringOff = true;
				startTimeout(&powerOffTimeout, ((uint32_t)global_header.sleep_delay) * 50);
			}
						
			// Cancel the power off timeout if the start button was released:
			if (possiblyPoweringOff && buttons[B_START].state == BUTTON_RELEASED) {
				possiblyPoweringOff = false;
				cancelTimeout(&powerOffTimeout);
			}
			// Start the power off timeout if the start button was just pressed:
			if (!possiblyBiosMode && buttons[B_SELECT].state != BUTTON_RELEASED ) {
				possiblyBiosMode = true;
				startTimeout(&biosModeTimeout, 2*((uint32_t)global_header.sleep_delay) * 50);
				displayWhichConfiguration(which_cfg);
			}
			
			// Cancel the power off timeout if the start button was released:
			if (possiblyBiosMode && buttons[B_SELECT].state == BUTTON_RELEASED) {
				possiblyBiosMode = false;
				cancelTimeout(&biosModeTimeout);
			}
			
		}
		if (checkTimeout(&joystickSampleTimeout)) {
			startTimeout(&joystickSampleTimeout, JOYSTICK_SAMPLE_TIMEOUT_MS);
			
			// Sample each of the joysticks:
			for (i = 0 ; i < NUM_JOYSTICKS; i++) {
				joysticks[i].previous_x = joysticks[i].current_x;
				joysticks[i].current_x  = sampleAnalogChannel(joysticks[i].adc_channel_x);
				
				joysticks[i].previous_y = joysticks[i].current_y;
				joysticks[i].current_y  = sampleAnalogChannel(joysticks[i].adc_channel_y);

				if (joystick_handler != NULL) {
					joystick_handler((enum JoystickName)i, joysticks[i].current_x, joysticks[i].current_y);
				}
			}
		}
		
		// Check if the start button has been held long enough to turn the device off:
		// Check if controller has been sitting idle long enough to turn the device off:
		if( checkTimeout(&powerOffTimeout) || checkTimeout(&powerOffUnused) )
		{
			cancelTimeout(&powerOffTimeout);
			cancelTimeout(&powerOffUnused);
			setLEDValue(0, 0, 0);
			powerOff(global_header.powerOffSoftware);
		}
		
		// Check if the select button has been held long enough to clear paired bluetooth list:
		if( checkTimeout(&biosModeTimeout) )
		{
			cancelTimeout(&biosModeTimeout);
			bt_exitBypass();
			btClearAutoConnectList();
			setLEDValue(LED_OFF, LED_OFF, LED_OFF);
			delay_ms(1500);
			reset_do_soft_reset();
		}
		
		// Check for commands from the computer:
		processComm();
	}
}

void maintainControllerStatus(bool pulse)
{
	bool bluetoothConnected = btIsConnected();
	
	// enum ChargeState batteryChargeState;
	enum ChargeState batteryChargeState = !ioport_get_pin_level(CHRG_STAT_PIN) ? FullyCharged : Charging;
	
	uint16_t battery_level = sampleAnalogChannel(ADCCH_POS_PIN3);
	setLEDValue(LED_OFF, LED_OFF, LED_OFF);

	if (bluetoothConnected) // Playing
	{
		if (batteryChargeState == Charging)
		{
			if (battery_level < BATTERY_HIGH_THRESHOLD)
			{
				// Bluetooth Connected
				// Charging
				// Battery Still Below Full Charge
				// Show the users that we still need to charge
				setGreenLEDValue(LED_DIM);
			}
			else
			{
				// Default State
				setBlueLEDValue(LED_DIM); // Default to blue
			}
		}
		else // Not Charging
		{
			if (battery_level < BATTERY_LOW_THRESHOLD)
			{
				// Indicate: Needs Charging
				setGreenLEDValue((pulse) ? LED_DIM : LED_OFF); // Blink green
			}
			else
			{
				// Normal - Ideal State
				setBlueLEDValue(LED_DIM); // Default to blue
			}
		}
	}
	else // Bluetooth not connected
	{
		setBlueLEDValue((pulse) ? LED_DIM : LED_OFF); // Blink blue
		return;
	}
}

void sysTickCallback(void) {
	static unsigned int wdtCheckCount = 0;
	// Clear the interrupt flag:
	clearSysTickFlag();
	
	// Increment system time:
	tickSystemTime();
	
	/* Check for time to validate system is still running */
	wdtCheckCount++;
	if (wdtCheckCount >= SYSTICK_FREQUENCY) {
		wdtCheckCount = 0;
		WatchdogValidate();
	}
}

void selectHandlers(void) {
	switch (ccc.mode) {
		case BTM_KEYBOARD_MOUSE:
			button_handler_init = &keyboardMouseInit;
			button_handler      = &keyboadMouseButtonHandler;
			joystick_handler    = &keyboardMouseJoystickHandler;
			break;
			
		case BTM_IOS_KEYBOARD:
			button_handler_init = &keyboardiOSInit;
			button_handler      = &keyboardiOSButtonHandler;
			joystick_handler    = NULL;
			break;

		case BTM_KEYBOARD:
			button_handler_init = &keyboardInit;
			button_handler      = &keyboardButtonHandler;
			joystick_handler    = &keyboardJoystickHandler;
			break;
		
		case BTM_JOYSTICK_ANALOG:
			button_handler_init = &jStickInit;
			button_handler      = &jStickButtonHandler;
			joystick_handler    = &jStickJoystickHandler;
			break;
		
		case BTM_GAMEPAD:
			button_handler_init = &gamepadInit;
			button_handler      = &gamepadButtonHandler;
			joystick_handler    = &gamepadJoystickHandler;
			break;
		
		default:
			button_handler_init = NULL;
			button_handler      = NULL;
			joystick_handler    = NULL;
			break;
	}
}

//Setup START_PIN external interrupt
void SetupStartPinExternalInterrupt()
{
	irqflags_t flags;
	flags = cpu_irq_save();
	
	PORTF_INT0MASK = 1u<<2; //Set PORTF interrupt on PORTF.2 pin
	arch_ioport_set_pin_sense_mode(START_PIN,IOPORT_SENSE_RISING);
	PORTF_INTCTRL = 2u; //Enable medium level external interrupt
	
	cpu_irq_restore(flags);
}

// PORTF interrupt vector, Vector 0 is the reset vector
ISR(PORTF_INT0_vect)
{
	irqflags_t flags;
	flags = cpu_irq_save();
	
	// If interrupt0 flag is set, clear it
	#define INT0IF 1u<<0
	#define INT1IF 1u<<1
	if( PORTF_INTFLAGS & INT0IF )
	{
		PORTF_INTFLAGS = INT0IF; // write-1-to-clear - to clear interrupt flag write a '1'
	}
	
	if (!turnedOn)
	{
		reset_do_soft_reset();
	}
	
	cpu_irq_restore(flags);
}
