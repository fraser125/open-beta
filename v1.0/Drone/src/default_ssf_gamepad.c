/*
 * default_ssf_gamepad.c
 * Version: Drone 1.0
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

#include "default_configurations.h"

const struct ControllerConfiguration DEFAULT_SSF_GAMEPAD_CONFIG = {
	.mode = BTM_KEYBOARD_MOUSE,
	.button_configs = {
		{ // UP
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.keyboard_and_mouse = {
				.input_type = INPUT_TYPE_KEYBOARD
			},
			.button_down = {
				.scan_code = 'w'-'a'+4
				//.scan_code = 0x52
			}
		},
		{ // DOWN
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.keyboard_and_mouse = {
				.input_type = INPUT_TYPE_KEYBOARD
			},
			.button_down = {
				.scan_code = 's'-'a'+4
				//.scan_code = 0x51
			}
		},
		{ // LEFT
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.keyboard_and_mouse = {
				.input_type = INPUT_TYPE_KEYBOARD
			},
			.button_down = {
				.scan_code = 'a'-'a'+4
				//.scan_code = 0x50
			}
		},
		{ // RIGHT
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.keyboard_and_mouse = {
				.input_type = INPUT_TYPE_KEYBOARD
			},
			.button_down = {
				.scan_code = 'd'-'a'+4
				//.scan_code = 0x4F
			}
		},
		{ // A or button 4
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.keyboard_and_mouse = {
				.input_type = INPUT_TYPE_KEYBOARD
			},
			.button_down = {
				.scan_code = 0x2C
				
			}
		},
		{ // B or button 3
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.keyboard_and_mouse = {
				.input_type = INPUT_TYPE_KEYBOARD
			},
			.button_down = {
				.scan_code = 0x58
			}
		},
		{ // X or button 1
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.keyboard_and_mouse = {
				.input_type = INPUT_TYPE_KEYBOARD
			},
			.button_down = {
				.scan_code = 0x4E
			}
		},
		{ // Y or button 2
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.keyboard_and_mouse = {
				.input_type = INPUT_TYPE_KEYBOARD
			},
			.button_down = {
				.scan_code = 0x4B
			}
		},
		{ // START
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.keyboard_and_mouse = {
				.input_type = INPUT_TYPE_KEYBOARD
			},
			.button_down = {
				.scan_code = 0x2B
			}
		},
		{ // SELECT
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.keyboard_and_mouse = {
				.input_type = INPUT_TYPE_KEYBOARD
			},
			.button_down = {
				.scan_code = 0x3E
			}
		},
		{ // RB
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.keyboard_and_mouse = {
				.input_type = INPUT_TYPE_KEYBOARD
			},
			.button_down = {
				.scan_code = 0x4D
			}
		},
		{ // LB
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.keyboard_and_mouse = {
				.input_type = INPUT_TYPE_KEYBOARD
			},
			.button_down = {
				.scan_code = 0X4A
			}
		},
	},
	.joystick_configs = {
		{ // LEFT JOYSTICK
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.button_up = {
				.scan_code = 'w'-'a'+4
			},
			.button_down = {
				.scan_code = 's'-'a'+4
			},
			.button_left = {
				.scan_code = 'a'-'a'+4
			},
			.button_right = {
				.scan_code = 'd'-'a'+4
			},
			.x_min = 2000,
			.x_max = 3500,
			.y_min = 2000,
			.y_max = 3500,
			.x_deadzone = 350,
			.y_deadzone = 350
		},
		{ // RIGHT JOYSTICK
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.button_up = {
				.scan_code = 'w'-'a'+4
			},
			.button_down = {
				.scan_code = 's'-'a'+4
			},
			.button_left = {
				.scan_code = 'a'-'a'+4
			},
			.button_right = {
				.scan_code = 'd'-'a'+4
			},
			.x_min = 2000,
			.x_max = 4000,
			.y_min = 2000,
			.y_max = 4000,
			.x_deadzone = 350,
			.y_deadzone = 350
			
		}
	}
};
