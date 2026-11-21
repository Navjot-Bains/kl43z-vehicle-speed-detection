/*
 * Copyright 2016-2026 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    sensors_interrupts.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL43Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL43Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    SIM->SCGC5 |= (1 << 9)| (1 << 12) | (1 << 13);

    PORTD->PCR[3] = 0x103; // IR1
    PORTA->PCR[4] = 0x103; // IR2
    PORTD->PCR[5] = 0x100; // LEDG
    PORTE->PCR[31] = 0x100; // LEDR

    PTD->PDDR &= ~(1 << 3);
    PTA->PDDR &= ~(1 << 4);
    PTD->PDDR |= (1 << 5);
    PTE->PDDR |= (1 << 31);

    // 3. Interrupt config.
    __disable_irq();
    NVIC_DisableIRQ(PORTC_PORTD_IRQn);
    NVIC_DisableIRQ(PORTA_IRQn);


    PORTD->PCR[3] &= ~(0xF000);
    PORTD->PCR[3] |= (0xA0000);

    PORTA->PCR[4] &=~(0xF000);
    PORTA->PCR[4] |= (0xA0000);


    NVIC_SetPriority(PORTC_PORTD_IRQn, 128);
    NVIC_ClearPendingIRQ(PORTC_PORTD_IRQn);

    NVIC_SetPriority(PORTA_IRQn, 128);
    NVIC_ClearPendingIRQ(PORTA_IRQn);


    NVIC_EnableIRQ(PORTC_PORTD_IRQn);
    NVIC_EnableIRQ(PORTA_IRQn);
    __enable_irq();


    while(1) { 
    	__asm volatile ("nop");
    }
    return 0 ;
}

void PORTA_IRQHandler(void){
	if(PORTA->ISFR & (1 << 4)){ 
		PORTA->PCR[4] |= PORT_PCR_ISF_MASK;
		PTE->PTOR = (1 << 31);
	}
}


void PORTC_PORTD_IRQHandler(void){
	if(PORTD->ISFR & (1 << 3)){ 
		PORTD->PCR[3] |= PORT_PCR_ISF_MASK;
		PTD->PTOR = (1 << 5); 
	}
}
