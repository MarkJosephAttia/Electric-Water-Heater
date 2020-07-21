#include "Std_Types.h"
#include "Gpio.h"
#include "Led.h"

const led_t Led_leds[LED_NUMBER_OF_LEDS] = {
    {GPIO_PIN_7, GPIO_PORTB, GPIO_PIN_SET}
};
