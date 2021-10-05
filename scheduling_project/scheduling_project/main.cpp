#include "scheduler.h" //scheduler �ȿ� PCB ����. 
#include "PCB.h"
#include <iostream>


int main()
{
    ProcessControlBlock IO_PCB_(Priority::high, IOStatus::exist);
    ProcessControlBlock non_IO_PCB_(Priority::middle, IOStatus::no);
    ProcessControlBlock non_IO_PCB_2(Priority::low, IOStatus::no);

    Scheduler scheduler{};

    //copy constructor�� ���� stack memory�� PBC�� heap���� ���� �Ҵ� ��.
    scheduler.LoadPCBs(IO_PCB_);
    scheduler.LoadPCBs(non_IO_PCB_);
    scheduler.LoadPCBs(non_IO_PCB_2);

    while(!scheduler.IsEmpty()) // ������ ������ �ǹ��� ���� �̸� ����.
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