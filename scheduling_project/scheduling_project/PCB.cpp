#include "PCB.h"
#include "scheduler.h"
#include <iostream>
using namespace std;

int ProcessControlBlock::PCB_num = 0;

//ProcessControlBlock::ProcessControlBlock() : process_id(PCB_num)
//{
//    cout << "Process constructed" << endl;
//    PCB_num++;
//    next_pcb = nullptr;
//    state = Status::new_;
//}

ProcessControlBlock::ProcessControlBlock(const Priority prior, const bool has_IO) : priority(prior), process_id(PCB_num), have_IO(has_IO) // const를 runtime에 결정하는 유일한 방법은 initialized list
{
    cout << "Process constructed" << endl;
    PCB_num++;
    next_pcb = nullptr;
    state = Status::new_;
}
ProcessControlBlock::ProcessControlBlock(const ProcessControlBlock& PCB) : process_id(PCB_num)
{
    cout << "Process constructed" << endl;
    PCB_num++;
    next_pcb = nullptr;
    state = Status::new_;
    have_IO = PCB.HaveIO();
    priority = PCB.GetPrior();
}

ProcessControlBlock::~ProcessControlBlock()
{
    cout << "Process exit" << endl;
}

bool ProcessControlBlock::HaveIO()const
{
    return have_IO;
}

Priority ProcessControlBlock::GetPrior()const
{
    return priority;
}

void ProcessControlBlock::SetPrior(const Priority& p)
{
    priority = p;
}



void ProcessControlBlock::PrintStatus() const
{
    cout << "Process ID : " << process_id << endl;
    cout << "Priorriy : " << static_cast<int>(priority) << endl;
    cout << "environment variable : " << environment_variable << endl;
}

void ProcessControlBlock::SetStatus(const Status stat)
{
    state = stat;
}

void ProcessControlBlock::SetNextPointer(ProcessControlBlock* const ptr_Pcb)
{
    next_pcb = ptr_Pcb;
}

ProcessControlBlock* ProcessControlBlock::GetNextPointer() const
{
    return next_pcb;
}

