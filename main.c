#include "Cfg.h"
#include "Std_Types.h"
#include "Sched.h"
#define _XTAL_FREQ 8000000

void main(void) 
{
    Sched_Init();
    Sched_Start();
    while(1);
    return;
}
