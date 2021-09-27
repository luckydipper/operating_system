#include "PCB.h"
#include "scheduler.h"
#include <iostream>
using namespace std;

int ProcessControlBlock::PCB_num = 0;

ProcessControlBlock::ProcessControlBlock() : process_id(PCB_num)
{
    cout << "Process constructed" << endl;
    PCB_num++;
    next_pcb = nullptr;
    state = Status::new_;
}

ProcessControlBlock::ProcessControlBlock(const Priority prior) : priority(prior), process_id(PCB_num) // const를 runtime에 결정하는 유일한 방법은 initialized list
{
    cout << "Process constructed" << endl;
    PCB_num++;
    next_pcb = nullptr;
    state = Status::new_;
}

ProcessControlBlock::~ProcessControlBlock()
{
    cout << "Process exit" << endl;
}

void ProcessControlBlock::PrintStatus() const
{
    cout << "Process ID : " << process_id << endl;
    cout << "Priorriy : " << static_cast<int>(priority) << endl;
    cout << "environment variable : " << environment_variable << endl;
}

void ProcessControlBlock::SetPointer(ProcessControlBlock* ptr_Pcb)
{
    next_pcb = ptr_Pcb;
}


