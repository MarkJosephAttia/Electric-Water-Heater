/**
 * @file Int.h
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the user interface for the interrupts
 * @version 0.1
 * @date 2020-07-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef INTERRUPT_H_
#define INTERRUPT_H_

typedef void (*interruptCb_t)(void);

extern interruptCb_t Timer1_func;

#endif