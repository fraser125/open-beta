/*
 * battery_charger.c
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

#include <asf.h>
#include "battery_charger.h"
#include "RGB_LED.h"

#define PIN_CHECK_DELAY_US 20

enum ChargeState getChargeState()
{
	/*
		Charge Cycle State - MCP73831
		Shutdown             Hi-Z
		No Battery Present   Hi-Z
		Preconditioning      L
		Constant-Current     L
		Constant Voltage     L
		Charge Complete      H
	*/
	
	enum ChargeState toRet = Error;
	
	// Check for HIGH state:
	// Enable the pull-down and look for a high state:
	ioport_set_pin_mode(CHRG_STAT_PIN, IOPORT_MODE_PULLDOWN);
	delay_us(PIN_CHECK_DELAY_US);
	
	// Is the pin still high?
	if (ioport_get_pin_level(CHRG_STAT_PIN) == 1) {
		toRet = FullyCharged;
	}
	else {
		// Next, check for low state:
		// Enable the pull-up and look for a low state:
		ioport_set_pin_mode(CHRG_STAT_PIN, IOPORT_MODE_PULLUP);
		delay_us(PIN_CHECK_DELAY_US);
		
		// Is the pin still low?
		if (ioport_get_pin_level(CHRG_STAT_PIN) == 0) {
			toRet = Charging;
		}
	}
	
	// Return the pin to it's normal setup:
	ioport_set_pin_mode(CHRG_STAT_PIN, IOPORT_MODE_TOTEM);

	// If it wasn't high or low, then it must be hi-z:
	return toRet;
}
