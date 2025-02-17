#include "interrupts.h"


void NVIC_EnableIRQ(uint32_t IRQ_NO)
{
    if (IRQ_NO > 63) // Cortex-M3 supports up to 64 IRQs (ISER[0] & ISER[1])
        return;

    if (IRQ_NO < 32) {
        NVIC->ISER[0] |= (1U << IRQ_NO);
    } else {
        NVIC->ISER[1] |= (1U << (IRQ_NO - 32));
    }
}
