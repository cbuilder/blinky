/* blinky.c - Simple example to blink the on-board LED. */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "CMSIS/Core/Include/cmsis_gcc.h"

int test_bss_counter;

int
main(void)
{
    volatile uint32_t ui32Loop;
    uint32_t primask;
    primask = __get_PRIMASK();
    __set_PRIMASK(1);
    // Enable the GPIO port that is used for the on-board LED.
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    // Check if the peripheral access is enabled.
    while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {
        ;
    }

    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);

    while(1)
    {
        ROM_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0);
        for(ui32Loop = 0; ui32Loop < 100000*test_bss_counter; ui32Loop++)
            ;
        ROM_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 , GPIO_PIN_1);
        for(ui32Loop = 0; ui32Loop < 100000; ui32Loop++)
            ;
	test_bss_counter+=1;
    }
}
