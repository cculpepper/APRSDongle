/*
 * Copyright (c) 12.2013, Martin Kojtal (0xc0170)
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
#include "main.h"
#include "common.h"
/*#include "cw.h"*/
/*#include "uart.h"*/

int main(void)
{
	int i;
    gpio_init();

    PTB->PSOR = (1U << 6U);
    PTB->PSOR = (1U << 7U);

    while (1) {
	for(i = 0;i<1000000;i++);
        PTB->PTOR = (1U << 6U);
    }
}




void gpio_init(void)
{
    SIM->SCGC5 = SIM_SCGC5_PORTB_MASK;
    PORTB->PCR[6] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
    PORTB->PCR[7] = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
    PTB->PDDR = (1U << 6U);
    PTB->PDDR = (1U << 7U);
}

