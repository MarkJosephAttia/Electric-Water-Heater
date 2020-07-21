/**
 * @file Adc.h
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This file is the user interface for the ADC driver
 * @version 0.1
 * @date 2020-03-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef ADC_H
#define ADC_H

#define ADC_CH_0                    0b000000
#define ADC_CH_1                    0b001000
#define ADC_CH_2                    0b010000
#define ADC_CH_3                    0b011000
#define ADC_CH_4                    0b100000
#define ADC_CH_5                    0b101000
#define ADC_CH_6                    0b110000
#define ADC_CH_7                    0b111000

typedef uint16_t Adc_Value_t;
typedef uint8_t Adc_Channel_t;

/**
 * @brief The ADC port and configurations initialization
 * 
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Adc_Init(void);
/**
 * @brief Gets the value of a specific channel
 * 
 * @param value the value that will be returned
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Adc_GetValue(Adc_Value_t* value);
/**
 * @brief Selects An Adc Channel
 * 
 * @param channel The Channel To Be Selected
 *                  @arg ADC_CH_x
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Adc_SelectChannel(Adc_Channel_t channel);
#endif