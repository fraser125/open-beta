/*
 * shared.h
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

#ifndef SHARED_H_
#define SHARED_H_
#include "asf.h"

// http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=40338
#define BIT(pin) (1 << (pin))

#define CLEARBIT(bite,pin) CLEARBITS((bite), (BIT((pin))))
#define CLEARBITS(bite,pin) ((bite) &= (~(pin)))

#define SETBIT(bite,pin) SETBITS((bite), (BIT((pin))))
#define SETBITS(bite,pin) ((bite) |= (pin))

#define BITSET(bite,pin) ((bite) & (BIT(pin)))
#define BITSSET(bite,pin) (((bite) & (pin)) == (pin))

#define BITCLEAR(bite,pin) !BITSET((bite), (pin))
#define BITSCLEAR(bite,pin) (((bite) & (pin)) == 0)

#define SETBITVALUE(bite,pin,val) (val ? BITSET(bite,pin) : BITCLEAR(bite,pin))
#define BITVAL(bite,pin) (((bite)>>(pin)) & 1)

void bootloader(void);

int16_t map(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max);

#endif /* SHARED_H_ */