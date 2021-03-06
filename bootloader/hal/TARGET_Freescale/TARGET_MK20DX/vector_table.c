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
#define NVIC_NUM_VECTORS (16 + 46)            // CORE + MCU Peripherals
#define NVIC_RAM_VECTOR_ADDRESS (0x1FFFE000)  // Vectors positioned at start of RAM

#elif defined(TARGET_MK21DX)
#include <MK21DA5.h>
#define NVIC_NUM_VECTORS (16 + 65)            // CORE + MCU Peripherals
#define NVIC_RAM_VECTOR_ADDRESS (0x1FFFC000)  // Vectors positioned at start of RAM

#elif defined(TARGET_MK22DN)
#include <MK22D5.h>
#define NVIC_NUM_VECTORS (16 + 65)            // CORE + MCU Peripherals
#define NVIC_RAM_VECTOR_ADDRESS (0x1FFF8000)  // Vectors positioned at start of RAM

#elif defined(TARGET_MKL82Z)
#include <MKL82Z7.h>
#define NVIC_NUM_VECTORS (16 + 32)
#define NVIC_RAM_VECTOR_ADDRESS (0x1FFFA000)

#endif
#include "vector_table.h"
#include "flash_hal.h"


void relocate_vector_table() {
    uint32_t *vectors;
    uint32_t i;

    // Copy and switch to dynamic vectors if the first time called
    if (SCB->VTOR != NVIC_RAM_VECTOR_ADDRESS) {
        uint32_t *old_vectors = (uint32_t*)START_APP_ADDRESS;
        vectors = (uint32_t*)NVIC_RAM_VECTOR_ADDRESS;
        for (i=0; i<NVIC_NUM_VECTORS; i++) {
            vectors[i] = old_vectors[i];
        }
        SCB->VTOR = (uint32_t)NVIC_RAM_VECTOR_ADDRESS;
    }
}
