/*
 * bios.c
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

#include "shared.h"
#include "buttons.h"
#include "joysticks.h"
#include "RGB_LED.h"
#include "watchdog.h"
#include "system_time.h"
#include "configurations.h"
#include "powerControl.h"
#include "shared.h"
#include "analog.h"

#define BIOS_UNUSED_MS 150000

struct GlobalHeader global_header;  // The current global header.
struct Timeout biosUnused; 

void biosMain(void);
void ManufactureTestButtonPress(void);

void biosMain(void)
{
	setupLEDs(false);
	setLEDValue(LED_OFF, LED_OFF, LED_OFF);
		
	setLEDValue(LED_ON, LED_OFF, LED_OFF);
	delay_ms(200);
	setLEDValue(LED_OFF, LED_OFF, LED_OFF);
	delay_ms(200);
	setLEDValue(LED_ON, LED_OFF, LED_OFF);
	delay_ms(200);
	setLEDValue(LED_OFF, LED_OFF, LED_OFF);
	delay_ms(200);
	setLEDValue(LED_ON, LED_OFF, LED_OFF);
	delay_ms(200);
	
	ManufactureTestButtonPress();

}

void ManufactureTestButtonPress(void)
{
	startTimeout(&biosUnused, BIOS_UNUSED_MS);
	while(1)
	{
		setLEDValue(LED_OFF, LED_OFF, LED_OFF);
		WatchdogPet();
		
		if (buttonActivated(B_START) & buttonActivated(B_SELECT))
		{
			delay_ms(500);
			reset_do_soft_reset();
		}
		
		if(checkTimeout(&biosUnused))
		{
			cancelTimeout(&biosUnused);
			setLEDValue(0, 0, 0);
			powerOff(global_header.powerOffSoftware);
		}

		if (buttonActivated(B_UP))
		{
			setGreenLEDValue(LED_ON);
		}
		else if (buttonActivated(B_DOWN))
		{
			setGreenLEDValue(LED_ON);
		}
		else if (buttonActivated(B_LEFT))
		{
			setGreenLEDValue(LED_ON);
		}
		else if (buttonActivated(B_RIGHT))
		{
			setGreenLEDValue(LED_ON);
		}
		else if (buttonActivated(B_A))
		{
			setGreenLEDValue(LED_ON);
		}
		else if (buttonActivated(B_B))
		{
			setGreenLEDValue(LED_ON);
		}
		else if (buttonActivated(B_X))
		{
			setGreenLEDValue(LED_ON);
		}
		else if (buttonActivated(B_Y))
		{
			setGreenLEDValue(LED_ON);
		}
		else if (buttonActivated(B_START))
		{
			setGreenLEDValue(LED_ON);
		}
		else if (buttonActivated(B_SELECT))
		{
			setGreenLEDValue(LED_ON);
		}
		else if (buttonActivated(B_LB))
		{
			setGreenLEDValue(LED_ON);
		}
		else if (buttonActivated(B_RB))
		{
			setGreenLEDValue(LED_ON);
		}
		else if (buttonActivated(B_LT))
		{
			setGreenLEDValue(LED_ON);
		}
		else if (buttonActivated(B_RT))
		{
			setGreenLEDValue(LED_ON);
		}
		
		uint16_t idx; // temporary variable.
		for (idx = 0 ; idx < NUM_JOYSTICKS; idx++) {
			uint16_t x_result, y_result;
			x_result = sampleAnalogChannel(joysticks[idx].adc_channel_x);
			y_result = sampleAnalogChannel(joysticks[idx].adc_channel_y);
			// Hard Coded Dead Zone so all LED's can be used for other buttons
			if (x_result > 3500)
			{			
				//X = Red
				setRedLEDValue(LED_ON);
			}
			if (y_result > 3500)
			{
				// Y = Blue
				setBlueLEDValue(LED_ON);			
			}
		}			
	}
}