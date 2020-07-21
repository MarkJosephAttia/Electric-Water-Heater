#include "Std_Types.h"
#include "Gpio.h"
#include "Element.h"

const element_t Element_elements[ELEMENT_NUMBER_OF_ELEMENTS] = {
    {GPIO_PIN_5, GPIO_PORTC, GPIO_PIN_SET},
    {GPIO_PIN_2, GPIO_PORTC, GPIO_PIN_SET}
};
