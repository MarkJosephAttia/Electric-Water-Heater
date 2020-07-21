/**
 * @file Adc.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief The implementation for the ADC driver
 * @version 0.1
 * @date 2020-03-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "Gpio.h"
#include "Adc.h"

/* The ADC Registers */
#define ADC_CON0_REG            *(uint8_t*)0x1F
#define ADC_CON1_REG            *(uint8_t*)0x9F
#define ADC_DATA_H              *(uint8_t*)0x1E
#define ADC_DATA_L              *(uint8_t*)0x9E
/* The ADC Masks */
#define ADC_CONV_DONE            0x04
#define ADC_CONV_START           0x04
#define ADC_CH_CLR              0xC7
/* The ADC Initial Configurations */
#define ADC_INIT_CONF_CON0      0x01
#define ADC_INIT_CONF_CON1      0x80



/**
 * @brief The ADC port and configurations initialization
 * 
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Adc_Init(void)
{
    /* Setting ADC Configuration Registers With Their Initial Values */
    ADC_CON0_REG = ADC_INIT_CONF_CON0;
    ADC_CON1_REG = ADC_INIT_CONF_CON1;
    return E_OK;
}

/**
 * @brief Gets the value of a specific channel
 * 
 * @param value the value that will be returned
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Adc_GetValue(Adc_Value_t* value)
{
    /* Start The Conversion */
    ADC_CON0_REG |= ADC_CONV_START;
    /* Wait For The Conversion */
    while(ADC_CON0_REG & ADC_CONV_DONE);
    /* Save The Data */
    *value = (ADC_DATA_H << 8) | ADC_DATA_L;
    return E_OK;
}

/**
 * @brief Selects An Adc Channel
 * 
 * @param channel The Channel To Be Selected
 *                  @arg ADC_CH_x
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Adc_SelectChannel(Adc_Channel_t channel)
{
    /* Initialize GPIO Pins For The Required Channel */
    gpio_t gpio = {
        .pins= GPIO_PIN_0,
        .mode= GPIO_MODE_INPUT,
        .port= GPIO_PORTA};
    switch(channel)
    {
        case ADC_CH_1:
            gpio.pins = GPIO_PIN_1;
            gpio.port = GPIO_PORTA;
            break;
        case ADC_CH_2:
            gpio.pins = GPIO_PIN_2;
            gpio.port = GPIO_PORTA;
            break;
        case ADC_CH_3:
            gpio.pins = GPIO_PIN_3;
            gpio.port = GPIO_PORTA;
            break;
        case ADC_CH_4:
            gpio.pins = GPIO_PIN_5;
            gpio.port = GPIO_PORTA;
            break;
        case ADC_CH_5:
            gpio.pins = GPIO_PIN_0;
            gpio.port = GPIO_PORTE;
            break;
        case ADC_CH_6:
            gpio.pins = GPIO_PIN_1;
            gpio.port = GPIO_PORTE;
            break;
        case ADC_CH_7:
            gpio.pins = GPIO_PIN_2;
            gpio.port = GPIO_PORTE;
            break;
    }
    Gpio_InitPins(&gpio);
    /* Select The ADC Channel */
    ADC_CON0_REG &= ADC_CH_CLR;
    ADC_CON0_REG |= channel;
    return E_OK;
}