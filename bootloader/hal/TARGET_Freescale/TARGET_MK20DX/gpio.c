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
#elif defined(TARGET_MKL82Z)
#include <MKL82Z7.h>
#endif
#include "gpio.h"

void gpio_init(void) {
    // clock for LED and button
	#ifdef TARGET_MKL82Z
	SIM->SCGC5 |= SIM_SCGC5_PTD_MASK | SIM_SCGC5_PTB_MASK;
	#else
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTB_MASK;
	#endif

    // Green LED, only one LED available
    PORTD->PCR[GPIO_GREEN_LED_PIN] = PORT_PCR_MUX(1);
#ifdef TARGET_MKL82Z
    GPIOD->PDOR = 1UL << GPIO_GREEN_LED_PIN;
    GPIOD->PDDR = 1UL << GPIO_GREEN_LED_PIN;
#else
    PTD->PDOR = 1UL << GPIO_GREEN_LED_PIN;
    PTD->PDDR = 1UL << GPIO_GREEN_LED_PIN;
#endif

    // RST button
    PORTB->PCR[GPIO_RST_BTN_PIN] = PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_PFE_MASK | PORT_PCR_MUX(1);
}

void gpio_set_dap_led(uint8_t state) {
    if (state) {
#ifdef TARGET_MKL82Z
    	GPIOD->PCOR  |= 1UL << GPIO_GREEN_LED_PIN; // LED on
#else
        PTD->PCOR  |= 1UL << GPIO_GREEN_LED_PIN; // LED on
#endif
    } else {
#ifdef TARGET_MKL82Z
    	GPIOD->PSOR  |= 1UL << GPIO_GREEN_LED_PIN; // LED off
#else
        PTD->PSOR  |= 1UL << GPIO_GREEN_LED_PIN; // LED off
#endif
    }
}

void gpio_set_msd_led(uint8_t state) {
    gpio_set_dap_led(state);
}

void gpio_set_cdc_led(uint8_t state) {
    gpio_set_dap_led(state);
}

void time_delay_ms(uint32_t delay)
{
#if defined(TARGET_MK20DX)
    SIM->SCGC5 |= SIM_SCGC5_LPTIMER_MASK;
#elif defined(TARGET_MK21DX) || defined(TARGET_MK22DN)
    SIM->SCGC5 |= SIM_SCGC5_LPTMR_MASK;
#elif defined(TARGET_MKL82Z)
    SIM->SCGC5 |= SIM_SCGC5_LPTMR0_MASK;
#endif
    LPTMR0->CMR = delay;
    LPTMR0->PSR = LPTMR_PSR_PCS(1) | LPTMR_PSR_PBYP_MASK;
    LPTMR0->CSR |= LPTMR_CSR_TEN_MASK;
    while (!(LPTMR0->CSR & LPTMR_CSR_TCF_MASK));
    LPTMR0->CSR &= ~LPTMR_CSR_TEN_MASK;
}

uint8_t gpio_get_pin_loader_state(void) {
    time_delay_ms(2); //delay 2ms for pull-up enable
#ifdef TARGET_MKL82Z
    return (GPIOB->PDIR & (1UL << GPIO_RST_BTN_PIN));
#else
    return (PTB->PDIR & (1UL << GPIO_RST_BTN_PIN));
#endif
}


