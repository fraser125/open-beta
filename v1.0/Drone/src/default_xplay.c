/*
 * default_xplay.c
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

const struct ControllerConfiguration DEFAULT_XPLAY_CONFIG = {
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
				//.scan_code = 0x82
				.scan_code = 0x106
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
				//.scan_code = 0x81
				.scan_code = 0x105
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
				//.scan_code = 0x80
				.scan_code = 0x103
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
				//.scan_code = 0x79
				.scan_code = 0x108
				
			}
		},
		{ // X 
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.keyboard_and_mouse = {
				.input_type = INPUT_TYPE_KEYBOARD
			},
			.button_down = {
				.scan_code = 0x307
			}
		},
		{ // O 
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.keyboard_and_mouse = {
				.input_type = INPUT_TYPE_KEYBOARD
			},
			.button_down = {
				.scan_code = 0x305
			}
		},
		{ // Square 
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.keyboard_and_mouse = {
				.input_type = INPUT_TYPE_KEYBOARD
			},
			.button_down = {
				.scan_code = 0x307
			}
		},
		{ // Triangle 
			.config = {
				.button_type = BUTTON_TYPE_DIGITAL
			},
			.keyboard_and_mouse = {
				.input_type = INPUT_TYPE_KEYBOARD
			},
			.button_down = {
				.scan_code = 0x308
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
				.scan_code = 0x28
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
				.scan_code = 0x57
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
				.scan_code = 0x311
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
				.scan_code = 0x310
			}
		},
	},
								
	.joystick_configs = {
		{ // LEFT JOYSTICK
			.x_min = 2000,
			.x_max = 3500,
			.y_min = 2000,
			.y_max = 3500,
			.x_deadzone = 350,
			.y_deadzone = 350
		},
		{ // RIGHT JOYSTICK
			.x_min = 2000,
			.x_max = 3500,
			.y_min = 2000,
			.y_max = 3500,
			.x_deadzone = 350,
			.y_deadzone = 350
		}
	}
};

