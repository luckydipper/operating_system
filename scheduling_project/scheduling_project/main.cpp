#include "scheduler.h" //scheduler �ȿ� PCB ����. 
#include "PCB.h"
#include <vector>
// time interupt ���� enter�� ����

int main()
{
    //std::vector<ProcessControlBlock*> IO_PCB_arr(4);
    ProcessControlBlock PCB_1(Priority::high);
    ProcessControlBlock* ptr_PCB = new ProcessControlBlock(Priority::high);
    ProcessControlBlock* ptr_PCB2 = new ProcessControlBlock(Priority::high);

    ptr_PCB->SetPointer(ptr_PCB2);

    printf("hello world");
    ProcessControlBlock PCB_list[14];
    Scheduler sheduler();


    delete ptr_PCB;
    delete ptr_PCB2;
    return 0;
}