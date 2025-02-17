#ifndef _INT_H_
#define _INT_H_

#include <stdint.h>

void NVIC_EnableIRQ(uint32_t IRQ_NO);

#define MAX_ISER 2 //

/*
 *  Interrupt Set Enable Registers
 */
#define NVIC_ISER0 0xE000E100
#define NVIC_ISER1 (*(volatile uint32_t *)0xE000E104)
//#define NVIC_ISER2 (*(volatile uint32_t *)0xE000E108)
//#define NVIC_ISER3 (*(volatile uint32_t *)0xE000E10C)
//#define NVIC_ISER4 (*(volatile uint32_t *)0xE000E110)
//#define NVIC_ISER5 (*(volatile uint32_t *)0xE000E114)
//#define NVIC_ISER6 (*(volatile uint32_t *)0xE000E118)
//#define NVIC_ISER7 (*(volatile uint32_t *)0xE000E11C)

/*
 *  Interrupts CLear Enable registers
 */
#define NVIC_ICER0 (*(volatile uint32_t *)0xE000E180)
#define NVIC_ICER1 (*(volatile uint32_t *)0xE000E184)
//#define NVIC_ICER2 (*(volatile uint32_t *)0xE000E188)
//#define NVIC_ICER3 (*(volatile uint32_t *)0xE000E18C)
//#define NVIC_ICER4 (*(volatile uint32_t *)0xE000E190)
//#define NVIC_ICER5 (*(volatile uint32_t *)0xE000E194)
//#define NVIC_ICER6 (*(volatile uint32_t *)0xE000E198)
//#define NVIC_ICER7 (*(volatile uint32_t *)0xE000E19C)

/*
 *  Interrupts Priority Registers
 */
#define NVIC_IPR0 (*(volatile uint32_t *)0xE000E400)
#define NVIC_IPR1 (*(volatile uint32_t *)0xE000E404)
//#define NVIC_IPR2 (*(volatile uint32_t *)0xE000E408)
//#define NVIC_IPR3 (*(volatile uint32_t *)0xE000E41C)
//#define NVIC_IPR4 (*(volatile uint32_t *)0xE000E410)
//#define NVIC_IPR5 (*(volatile uint32_t *)0xE000E414)
//#define NVIC_IPR6 (*(volatile uint32_t *)0xE000E418)
//#define NVIC_IPR7 (*(volatile uint32_t *)0xE000E41C)




/**
 * UART IRQ
 */
#define UART_1_IRQ_POS 37
#define UART_2_IRQ_POS 38
#define UART_3_IRQ_POS 39
#define UART_4_IRQ_POS 52
#define UART_5_IRQ_POS 53

typedef struct
{
	volatile uint32_t ISER[2];
}NVIC_t;

#define NVIC ((NVIC_t *)NVIC_ISER0)

#endif
