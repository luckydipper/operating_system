#include "scheduler.h" //scheduler 안에 PCB 있음. 
#include "PCB.h"
#include <iostream>


int main()
{
    ProcessControlBlock IO_PCB_(Priority::high, IOStatus::exist);
    ProcessControlBlock non_IO_PCB_(Priority::middle, IOStatus::no);
    ProcessControlBlock non_IO_PCB_2(Priority::low, IOStatus::no);

    Scheduler scheduler{};

    //copy constructor를 통해 stack memory의 PBC를 heap으로 동적 할당 됨.
    scheduler.LoadPCBs(IO_PCB_);
    scheduler.LoadPCBs(non_IO_PCB_);
    scheduler.LoadPCBs(non_IO_PCB_2);

    while(!scheduler.IsEmpty()) // 다음엔 긍정인 의미의 변수 이름 쓰기.
    {
        scheduler.TimeExeption();
        scheduler.LongTermScheduling();
        scheduler.TimeExeption();
        scheduler.ShortTermScheduling();
        scheduler.PrintQueue();
        scheduler.TimeExeption();
        scheduler.IOScheduling();
    }
    return 0;
}