/*
 * drone_xplay_config.c
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

#include "drone_game_configurations.h"

const struct ControllerConfiguration DRONE_XPLAY_CONFIG = {
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
				//.scan_code = 
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
				//.scan_code = 
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
				//.scan_code = 
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
				//.scan_code = 				
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
				//.scan_code = 
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
				//.scan_code = 
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
				//.scan_code = 
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
				//.scan_code = 
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
				//.scan_code = 
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
				//.scan_code = 
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
				//.scan_code = 
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
				//.scan_code = 
			}
		},
	},
								
	.joystick_configs = {
		{ // LEFT JOYSTICK
			.x_min = 2000,
			.x_max = 4000,
			.y_min = 2000,
			.y_max = 4000,
			.x_deadzone = 475,
			.y_deadzone = 475
		},
		{ // RIGHT JOYSTICK
			.x_min = 2000,
			.x_max = 4000,
			.y_min = 2000,
			.y_max = 4000,
			.x_deadzone = 475,
			.y_deadzone = 475
		}
	}
};

