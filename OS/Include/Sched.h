/**
 * @file Sched.h
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This file is the user interface for the Scheduler
 * @version 0.1
 * @date 2020-03-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef SCHED_H
#define SCHED_H

typedef void (*taskRunnable_t)(void);

typedef struct
{
    taskRunnable_t runnable;
    uint32_t periodicTimeMS;

}task_t;

typedef struct
{
    const task_t* task;
    uint32_t delayTicks;
} sysTaskInfo_t;

/**
 * @brief The scheduler that will run all the time
 * 
 */
extern void Sched_Start(void);

/**
 * @brief The initialization for the Scheduler
 * 
 * @return Std_ReturnType 
 */
extern Std_ReturnType Sched_Init(void);

/**
 * @brief Suspends a running task
 * 
 * @return Std_ReturnType 
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Sched_SuspendTask(void);

/**
 * @brief Makes a task sleep for a while
 * 
 * @param timeMS The sleep time in milli seconds
 * @return Std_ReturnType 
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Sched_Sleep(uint32_t timeMS);

#endif