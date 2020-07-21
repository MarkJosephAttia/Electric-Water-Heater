/**
 * @file SSeg.h
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the user interface for the Seven Segment Display Driver
 * @version 0.1
 * @date 2020-07-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H
#include "SSeg_Cfg.h"

typedef struct
{
    Gpio_Pins_t dPin[SSEG_NUMBER_OF_PINS];
    Gpio_Port_t dPort[SSEG_NUMBER_OF_PINS];
    Gpio_Pins_t enPin[SSEG_NUMBER_OF_SSEGS];
    Gpio_Port_t enPort[SSEG_NUMBER_OF_SSEGS];
    uint8_t common[SSEG_NUMBER_OF_SSEGS];
} sseg_t;

typedef uint8_t SSeg_display_t;
typedef uint8_t SSeg_name_t;

/* The Seven Segment Type */
#define SSEG_COMMON_ANODE               'A'
#define SSEG_COMMON_CATHODE             'C'

/* The Seven Segment Display Status */
#define SSEG_ON                         0
#define SSEG_OFF                        !SSEG_ON

/**
 * @brief The Seven Segment initialization
 * 
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType SSeg_Init(void);
/**
 * @brief Sets A Digit For A Specific Seven Segment
 * 
 * @param name The Name Of The Seven Segment
 * @param digit The Digit To Set
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType SSeg_SetNum(SSeg_name_t name, uint8_t digit);
/**
 * @brief Sets The Seven Segments Display On And Off
 * 
 * @param display The Display State
 *              @arg SSEG_ON
 *              @arg SSEG_OFF
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType SSeg_SetDisplay(SSeg_display_t display);

#endif
