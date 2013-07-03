/*
 * joysticks.h
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

#ifndef JOYSTICKS_H_
#define JOYSTICKS_H_

#include <asf.h>

enum JoystickName {
	JOYSTICK_LEFT = 0,
	JOYSTICK_RIGHT,
	NUM_JOYSTICKS
};

struct Joystick {
	enum adcch_positive_input adc_channel_x, adc_channel_y;
	uint16_t center_x, center_y;
	uint16_t previous_x, previous_y;
	uint16_t current_x, current_y;
};

typedef void (*JoystickHandler)(enum JoystickName, int16_t /*x*/, int16_t /*y*/);

extern struct Joystick joysticks[NUM_JOYSTICKS];

#endif /* JOYSTICKS_H_ */