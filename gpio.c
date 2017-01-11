#include "inc/tm4c1294ncpdt.h"
#include "inc/hw_memmap.h"

//int32_t gpio_pin_output(uint32_t ui32Port, uint8_t ui8Pins)
int32_t gpio_pin_output()
{
// Enable the GPIO port that is used for the on-board LED.
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    // Check if the peripheral access is enabled.
    while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {
        ;
    }
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    return 0;
}