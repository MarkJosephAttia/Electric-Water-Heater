/**
 * @file Sched.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This file is the implementation for the Scheduler
 * @version 0.1
 * @date 2020-03-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "Sched_Cfg.h"
#include "Sched.h"
#include "Int.h"
#include "Timer1.h"

/* Task States */
#define SCHED_TASK_RUNNING               1
#define SCHED_TASK_SUSPENDED             2
/* Flag States */
#define FLAG_RAISED                      1
#define FLAG_LOWERED                     0

typedef struct
{
    const sysTaskInfo_t* taskInfo;
    uint32_t remainToExec;
    uint32_t periodTicks;
    uint8_t state;
    uint32_t sleepTimes;
} sysTask_t;

typedef uint8_t Sched_Flag_t;

extern const sysTaskInfo_t Sched_sysTaskInfo[SCHED_NUMBER_OF_TASKS];

static sysTask_t Sched_task[SCHED_NUMBER_OF_TASKS];

static volatile Sched_Flag_t Sched_flag;

static volatile uint8_t Sched_taskItr;

/**
 * @brief Sets the scheduler flag
 * 
 */
static void Sched_SetFlag(void)
{
    /* Raise The Tick Flag */
    Sched_flag = FLAG_RAISED;
}

/**
 * @brief The scheduler that will run all the time
 * 
 */
void Sched_Start(void)
{
    Timer1_Start(TMR1_DIV_1);
    while(1)
    {
        /* If The Flag Is Raised */
        if(Sched_flag == FLAG_RAISED)
        {
            /* Lower The Flag */
            Sched_flag = FLAG_LOWERED;
            for(Sched_taskItr=0; Sched_taskItr<SCHED_NUMBER_OF_TASKS; Sched_taskItr++)
            {
                if(SCHED_TASK_RUNNING == Sched_task[Sched_taskItr].state)
                {
                    /* If The Task Is Ready To Execute */
                    if(0 == Sched_task[Sched_taskItr].remainToExec)
                    {
                        Sched_task[Sched_taskItr].remainToExec = Sched_task[Sched_taskItr].periodTicks;
                        Sched_task[Sched_taskItr].taskInfo->task->runnable();
                    }
                    else
                    {
                        /* Empty Else To Satisfy The Misra Rules */
                    }
                    
                    Sched_task[Sched_taskItr].remainToExec--;
                }
                else
                {
                    /* Empty Else To Satisfy The Misra Rules */
                }
                
            }
        }
        else
        {
            /* Empty Else To Satisfy The Misra Rules */
        }
        
    }
}

/**
 * @brief The initialization for the Scheduler
 * 
 * @return Std_ReturnType 
 */
Std_ReturnType Sched_Init(void)
{
    uint8_t i;
    for(i=0; i<SCHED_NUMBER_OF_TASKS; i++)
    {
        /* Initialize Tasks */
        Sched_task[i].taskInfo = &Sched_sysTaskInfo[i];
        Sched_task[i].remainToExec = Sched_task[i].taskInfo->delayTicks;
        Sched_task[i].periodTicks = Sched_task[i].taskInfo->task->periodicTimeMS / SCHED_TICK_TIME_MS;
        Sched_task[i].state = SCHED_TASK_RUNNING;
    }
    /* Initialize Timer 1 */
    Timer1_Stop();
    Timer1_SetTimeUS((f64)SCHED_SYS_CLK, SCHED_TICK_TIME_MS*1000);
    Timer1_SetCallBack(Sched_SetFlag);
    Timer1_ClearValue();
    Timer1_InterruptEnable();
    return E_OK;
}

/**
 * @brief Suspends a running task
 * 
 * @return Std_ReturnType 
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Sched_SuspendTask(void)
{
    Sched_task[Sched_taskItr].state = SCHED_TASK_SUSPENDED;
    return E_OK;
}

/**
 * @brief Makes a task sleep for a while
 * 
 * @param timeMS The sleep time in milli seconds
 * @return Std_ReturnType 
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Sched_Sleep(uint32_t timeMS)
{
    uint32_t times = timeMS / SCHED_TICK_TIME_MS;
    Sched_task[Sched_taskItr].remainToExec += times;
    return E_OK;
}