/*
* ManufactureValidation.c
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

#include "ManufactureValidation.h"
#include <asf.h>
#include "bluetooth.h"
#include "debug.h"
#include "RGB_LED.h"
#include "shared.h"
#include "strings.h"
#include "stdio.h"
#include "usb.h"
#include "battery_charger.h"
#include <avr\pgmspace.h>

//const uint8_t LED_ON = 50
//const uint8_t LED_OFF = 0

// These methods are private
void RunHandTestProcedure(void);
void Test0000(void);
void Test0001(void);
void Test0010(void);
void Test0011(void);
void Test0100(void);
void Test0101(void);
void Test0110(void);
void Test0111(void);

void Test1000(void);
void Test1001(void);
void Test1010(void);
void Test1011(void);

void Test1100(void);
void Test1101(void);
void Test1110(void);
void Test1111(void);

bool IsTestMode()
{
	return ioport_get_pin_level(IsManufactureTestMode);
}

void ExecuteTest()
{
	setupDbg();
	setupLEDs(false);
	// ReadPinLevels and test id's
		
	uint8_t testId;
	SETBITVALUE(testId, 0, ioport_get_pin_level(DRONE_GPIO_0));
	SETBITVALUE(testId, 1, ioport_get_pin_level(DRONE_GPIO_1));
	SETBITVALUE(testId, 2, ioport_get_pin_level(DRONE_GPIO_2));
	SETBITVALUE(testId, 3, ioport_get_pin_level(DRONE_GPIO_3));
	
	switch(testId)
	{
		case 0:{ RunHandTestProcedure(); } break;
		case 1:{ Test0001(); } break;
		case 2:{ Test0010(); } break;
		case 3:{ Test0011(); } break;
		case 4:{ Test0100(); } break;
		case 5:{ Test0101(); } break;
		case 6:{ Test0110(); } break;
		case 7:{ Test0111(); } break;
		case 8:{ Test1000(); } break;
		case 9:{ Test1001(); } break;
		case 10:{ Test1010(); } break;
		case 11:{ Test1011(); } break;
		case 12:{ Test1100(); } break;
		case 13:{ Test1101(); } break;
		case 14:{ Test1110(); } break;
		case 15:{ Test1111(); } break;
		default:{				
				sendDBGLine(unsupportedTest);
			}
	}
}

void RunHandTestProcedure(void)
{
	setLEDValue(LED_OFF, LED_OFF, LED_OFF);
	setBlueLEDValue(LED_ON);
	
	delay_ms(1800);
	sendBTCmd("BC:PC=08,01");
	sendBTCmd("BC:PC=09,00");
	
	while(ioport_get_pin_level(DRONE_GPIO_3) == false)
	{
		setLEDValue(LED_ON, LED_OFF, LED_OFF);
		delay_ms(200);
		setLEDValue(LED_OFF, LED_ON, LED_OFF);
		delay_ms(200);
		setLEDValue(LED_OFF, LED_OFF, LED_ON);
		delay_ms(200);
	}
}

// Ignored in initial release. It's a test test anyway. Just to prove the device goes in to test mode. 
void Test0000()
{	
	//sendDBGLine("Test0000: Drone in Test Mode");	
	printf(pgm_read_byte(testText),' ', 0, pgm_read_byte(testMode));
	
	setLEDValue(LED_OFF, LED_ON, LED_OFF);
	
	//sendDBGLine("Toggle GPIO pins for actual Tests");
	//sendDBGLine_P(testModeDirections);	
	sendDBGLine(testModeDirections);
	
	//sendDBGLine("/Test0000: Drone in Test Mode");	
	printf(pgm_read_byte(testText),'/', 0, pgm_read_byte(testMode));
}

void Test0001()
{
	setLEDValue(LED_OFF, LED_OFF, LED_OFF);	
	printf(pgm_read_byte(testText),' ', 0001, pgm_read_byte(btIOTest));	
	sendBTCmd(pgm_read_byte(dfumode));
	setBlueLEDValue(LED_ON);
	printf(pgm_read_byte(testText),'/', 0001, pgm_read_byte(btIOTest));	
	while(true){}
}

void Test0010()
{	
	printf(pgm_read_byte(testText),' ', 10, pgm_read_byte(ledTest));
	
	//sendDBGLine("Test0010: LED Test");
	while(ioport_get_pin_level(DRONE_GPIO_3) == false)
	{	
		setLEDValue(LED_ON, LED_OFF, LED_OFF);
		delay_ms(200);
		setLEDValue(LED_OFF, LED_ON, LED_OFF);
		delay_ms(200);
		setLEDValue(LED_OFF, LED_OFF, LED_ON);
		delay_ms(200);
	}	
	//sendDBGLine("/Test0010: ");
	printf(pgm_read_byte(testText),'/', 10, pgm_read_byte(ledTest));	
}

void Test0011()
{	
	printf(pgm_read_byte(testText),' ', 11, pgm_read_byte(usbTX));
	//sendDBGLine("Test0011: USB Transmit");	
	setLEDValue(LED_OFF, LED_OFF, LED_ON);
	setupUsb();
	while(ioport_get_pin_level(DRONE_GPIO_3) == false)
	{		
		//sendUSBLine("USB Transmit Test");
		sendUSBLine(pgm_read_byte(usbTXText));
		// Monitor USB TX/RX indicator line (USB-IO)		
	}		
	printf(pgm_read_byte(testText),'/', 11, pgm_read_byte(usbTX));
	//sendDBGLine("/Test0011: USB Transmit");	
}

void Test0100()
{	
	printf(pgm_read_byte(testText),' ', 100, pgm_read_byte(chargeStatus));
	//sendDBGLine("Test0100: Charge Status");		
	enum ChargeState chargeState = getChargeState();
	
	if (chargeState == Charging || chargeState == FullyCharged)
	{
		setLEDValue(LED_OFF, LED_ON, LED_OFF);
	}
	else
	{
		setLEDValue(LED_ON, LED_OFF, LED_OFF);
	}		
	
	//sendDBGLine("/Test0100: Charge Status");
	printf(pgm_read_byte(testText),'/', 100, pgm_read_byte(chargeStatus));		
}

void Test0101()
{	
	printf(pgm_read_byte(testText),' ', 101, pgm_read_byte(notImplementedTest));	
	//sendDBGLine("Test0101: ");
	//sendDBGLine("Test NOT IMPLEMENTED");	
	setLEDValue(LED_OFF, LED_OFF, LED_OFF);
	//sendDBGLine("/Test0101: ");
	printf(pgm_read_byte(testText),'/', 101, pgm_read_byte(notImplementedTest));		
}

void Test0110()
{
	setLEDValue(LED_OFF, LED_OFF, LED_OFF);
	//sendDBGLine("Test0110: ");
	char buffer[35];
	printf(pgm_read_byte(testText),' ', 110, pgm_read_byte(notImplementedTest));	
	if (hardwareflowcontrol(1000))
	{		
		//sendDBGLine("Bluetooth: FlowControl Works.");
		printf(pgm_read_byte(btFlowControlWorks));
		setGreenLEDValue(LED_ON);
	}			
	else
	{
		//sendDBGLine("Bluetooth: FlowControl FAIL");
		printf(pgm_read_byte(btFlowControlFail));
		setRedLEDValue(LED_ON);	
	}		
	//sendDBGLine("/Test0110: ");
	printf(pgm_read_byte(testText),'/', 110, pgm_read_byte(notImplementedTest));	
}

void Test0111()
{
	setLEDValue(LED_OFF, LED_OFF, LED_OFF);
	char buffer[35];
	sprintf(buffer,pgm_read_byte(testText),' ', 111, pgm_read_byte(btIOTest));
	//sendDBGLine("Test0111: ");
	printf(buffer);
	//sendBTCmd("BC:PC=08,01");
	sendBTCmd(pgm_read_byte(btIO8High));
	//sendBTCmd("BC:PC=09,00");	
	sendBTCmd(pgm_read_byte(btIO9Low));
	setBlueLEDValue(LED_ON);
	sprintf(buffer,pgm_read_byte(testText),'/', 111, pgm_read_byte(btIOTest));
	//sendDBGLine("/Test0111: ");
	printf(buffer);
}

void Test1000(void)
{
	return;	
}

void Test1001(void)
{
	return;
}

void Test1010(void)
{
	return;
}

void Test1011(void)
{
	return;
}

void Test1100(void)
{
	return;
}

void Test1101(void)
{
	return;
}

void Test1110(void)
{
	return;
}

void Test1111(void)
{
	char buffer[30];
	sprintf(buffer,pgm_read_byte(testText),' ', 1111, pgm_read_byte(voltageTests));
	//sendDBGLine("Test0001: Voltage Tests");
	printf(buffer);
	turnBTOn();
	setLEDValue(LED_OFF, LED_OFF, LED_ON);
	sprintf(buffer,pgm_read_byte(testText),'/', 1111, pgm_read_byte(resultsExternal));
	//sendDBGLine("/Test0001: Results External");
	printf(buffer);
while(true){}
}