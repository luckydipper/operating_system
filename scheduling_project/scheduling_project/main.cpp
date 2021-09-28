#include "scheduler.h" //scheduler 안에 PCB 있음. 
#include "PCB.h"

// time interupt 마다 enter를 누름

int main()
{
    ProcessControlBlock IO_PCB_(Priority::high, true);
    ProcessControlBlock non_IO_PCB_(Priority::middle, false);
    Scheduler scheduler;
    // 설계의 문제점. scheduler에서 PCB의 new와 delete를 생각하니, push만큼 pop이 없으면 메모리 누수가 남.
    // 생성자와 소멸자가 아닌 곳에서는 new와 delete를 하면 안 될 듯.
    scheduler.PushPCB(IO_PCB_);
    scheduler.PushPCB(IO_PCB_);
    scheduler.PushPCB(IO_PCB_);
    delete scheduler.PopPCB();
    delete scheduler.PopPCB();
    delete scheduler.PopPCB();
    return 0;
}