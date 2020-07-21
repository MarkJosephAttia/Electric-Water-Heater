/**
 * @file Int.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the implementation for the interrupts
 * @version 0.1
 * @date 2020-07-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "Int.h"

/* The Prihperal Interrupt Flags Register */
#define PIF                       *(uint8_t*)0x0C
/* Masks */
#define CCP1_INT_FLAG                        0x04
#define CCP1_INT_FLAG_CLR                    0xFB

/* Timer 1 Callback Function */
interruptCb_t Timer1_func = NULL;

/**
 * @brief Global Interrupt Service Routine
 * 
 */
void __interrupt() ISR()
{
    /* Check For CCP1 Interrupt */
    if(PIF & CCP1_INT_FLAG)
	{
        if(Timer1_func)
        {
            Timer1_func();
        }
        else
        {
            /* Empty Else To Satisfy The Misra Rules */
        }
        /* Clear The Flag */
        PIF &= CCP1_INT_FLAG_CLR;
    }
    else
    {
        /* Empty Else To Satisfy The Misra Rules */
    }
    
}