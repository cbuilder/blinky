/* blinky.c - Simple example to blink the on-board LED. */

#include <stdint.h>
#include <stdbool.h>
//#include "inc/tm4c1294ncpdt.h"
//#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "cmsis_gcc.h"
#include "core_cm4.h"
//#include "core_cmFunc.h"
#include "TM4C1294NCPDT.h"
#include "gpio.c"
#include "task.h"
//#include "ps1.c"

extern void ps1();

__attribute__((always_inline)) __STATIC_INLINE void __SVC(uint8_t sv_num)
{
  __ASM volatile ("SVC %0" : : "i" (sv_num));
}

void pin_toggle(uint32_t ui32Port, uint8_t ui8Pins)
{
    if (ui8Pins & ROM_GPIOPinRead(ui32Port, ui8Pins))
        ROM_GPIOPinWrite(ui32Port, ui8Pins, 0);
    else
        ROM_GPIOPinWrite(ui32Port, ui8Pins, ui8Pins);
}

void SysTick_Handler(void)
{
    ;
    pin_toggle(GPION_BASE, 1);
}

void SVC_Handler(void)
{
    /* Getting the svc number from last svc instruction */
    uint32_t *sp = (uint32_t *) __get_MSP();
    uint16_t *pcp = *(sp + 8);
    uint8_t svc_num = *(pcp - 1);
}

int
main(void)
{
    volatile uint32_t ui32Loop;
    
    __set_PRIMASK(1);
    //Start sysTickTimer
    SysTick_Config(0x100000);
    //Initialize timer interrupt
    NVIC_EnableIRQ(SysTick_IRQn);

    __set_PRIMASK(0);
    
    NVIC_EnableIRQ(SVCall_IRQn);
    __SVC(0x36);
    gpio_pin_output();

    register_task(idle, MIN_TSK_STACK_SIZE);
    register_task(ps1, 2*MIN_TSK_STACK_SIZE);
    //switch_psp();
    while(1)
    {
        for(ui32Loop = 0; ui32Loop < 1000000; ui32Loop++)
            ;
        pin_toggle(GPION_BASE, 0x2);
    }
}