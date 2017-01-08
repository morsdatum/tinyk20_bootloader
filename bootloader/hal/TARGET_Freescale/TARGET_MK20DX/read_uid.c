/* CMSIS-DAP Interface Firmware
 * Copyright (c) 2009-2013 ARM Limited
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
#if defined(TARGET_MK20DX)
#include <MK20D5.h>
#elif defined(TARGET_MK21DX)
#include <MK21DA5.h>
#elif defined(TARGET_MK22DN)
#include <MK22D5.h>
#endif
#include "read_uid.h"

void read_unique_id(uint32_t *id) {
    *id = SIM->UIDL ^ SIM->UIDML ^ SIM->UIDMH ^ SIM->UIDH;
}
