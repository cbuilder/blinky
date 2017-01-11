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

void psp_init(uint32_t stack_top)
{
    __set_PSP(stack_top);
}

void switch_psp()
{
    uint32_t control;
    control = __get_CONTROL();
    control |= 0x2; // PSP is the current stack pointer.
    __set_CONTROL(control);
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

int
main(void)
{
    volatile uint32_t ui32Loop;
    
    __set_PRIMASK(1);
    //Start sysTickTimer
    SysTick_Config(0x100000);
    //Initialize timer interrupt
    NVIC_EnableIRQ(SysTick_IRQn);

    psp_init(0x20000000+0x400);
    switch_psp();

    gpio_pin_output();

    __set_PRIMASK(0);

    while(1)
    {
        for(ui32Loop = 0; ui32Loop < 1000000; ui32Loop++)
            ;
        pin_toggle(GPION_BASE, 0x2);
    }
}