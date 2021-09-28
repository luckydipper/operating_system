// TODO : Pop and Push from job queue 구조가 비슷함.
// QUEUE로 따로 구현해놓고 JOB READY DEVICE 나눌껄...
// Load PCB에서 동적할당을 한번에 진행하
// CPU에서 각각 free
// 처음 구현할 때 stack pop을 구현해버림
        //ProcessControlBlock* temp = ready_rear;
        //ready_rear = ready_front;
        //// -2 because 
        //for (int i = 0; i < ready_length - 2; i++)
        //    ready_rear = ready_rear->GetNextPointer();
        //ready_length--;
        //return temp; //new malloc으로 받은 object여서 dangling pointer 안 일어남.
        //}

#include "scheduler.h"
#include <iostream>
#include <stdbool.h>
using namespace std;


Scheduler::Scheduler() : job_length(0), ready_length(0), device_length(0),
job_front(nullptr), job_rear(nullptr),
ready_front(nullptr), ready_rear(nullptr),
device_front(nullptr),device_rear(nullptr)
{ cout << "queue made" << endl; };

Scheduler::~Scheduler() { cout << "queue deleted" << endl; }

void Scheduler::TimeExeption()
{
    // to see what happening
    cout << "Time Interupt!" << endl;
    cout << "press any key and enter" << endl;
    PrintQueue();
    char input;
    cin >> input;
    return;
}

//set status new -> ready
// !caution! 
void Scheduler::JobPush(const ProcessControlBlock &PCB)
{
    ProcessControlBlock* ptr_PCB = (ProcessControlBlock*)&PCB;
    if (job_length == 0)
        job_front = job_rear = ptr_PCB;
    else
    {
        job_rear->SetNextPointer(ptr_PCB);
        job_rear = job_rear->GetNextPointer();
    }
    job_length++;
}

// caution : job_length != 0
// 지우는 과정을 넣지 않았음..
ProcessControlBlock* Scheduler::JobPop()
{
    ProcessControlBlock* temp = job_front; 
    job_front = job_front->GetNextPointer();
    job_length--;
    temp->SetNextPointer(nullptr);
    return temp; //new malloc으로 받은 object여서 dangling pointer 안 일어남.
}

// change status ready
void Scheduler::ReadyPush(const ProcessControlBlock& PCB)
{
    
    ProcessControlBlock* ptr_PCB = (ProcessControlBlock*)&PCB;
    ptr_PCB->SetStatus(Status::ready);
    if (ready_length == 0)
        ready_front = ready_rear = ptr_PCB;
    else
    {
        ready_rear->SetNextPointer(ptr_PCB);
        ready_rear = ready_rear->GetNextPointer();
    }
    ready_length++;
}

ProcessControlBlock* Scheduler::ReadyPop()
{
    ProcessControlBlock* temp = ready_front;
    ready_front = ready_front->GetNextPointer();
    ready_length--;
    temp->SetNextPointer(nullptr);
    return temp; //new malloc으로 받은 object여서 dangling pointer 안 일어남.
}

void Scheduler::DevicePush(const ProcessControlBlock& PCB)
{
    cout << "start IO PID : " << PCB.GetPID() << endl;
    ProcessControlBlock* ptr_PCB = (ProcessControlBlock*)&PCB;
    if (device_length == 0)
        device_front = device_rear = ptr_PCB;
    else
    {   
        device_rear->SetNextPointer(ptr_PCB);
        device_rear = device_rear->GetNextPointer();
    }
    device_length++;
}

ProcessControlBlock* Scheduler::DevicePop()
{
    ProcessControlBlock* temp = device_front;
    cout << "end IO PID : " << temp->GetPID() << endl;
    device_front = device_front->GetNextPointer();
    device_length--;
    temp->SetNextPointer(nullptr);
    temp->SetHaveIO(false);
    return temp; //new malloc으로 받은 object여서 dangling pointer 안 일어남.
}

// Job-> ready
void Scheduler::LongTermScheduling()
{
    if (job_length == 0)
        return;
    ReadyPush(*JobPop());
}

void Scheduler::ShortTermScheduling()
{
    if (ready_length == 0)
        return;
    ProcessControlBlock* from_ready = ReadyPop();
    if (from_ready->HaveIO())
        DevicePush(*from_ready); 
    else
        CpuProcess(*from_ready);
}

//change IO status
void Scheduler::IOScheduling()
{
    if (device_length == 0)
        return;
    ReadyPush(*DevicePop());
}

void Scheduler::CpuProcess(const ProcessControlBlock& PCB)
{
    cout << "Process PID : " << PCB.GetPID() << " Runing." << endl;
    delete &PCB;
}

void Scheduler::PrintQueue() const
{
    cout << "--------------------------------" << endl;
    cout << "In Job Queue: " << endl;
    ProcessControlBlock* ptr_dumy = job_front;
    while(ptr_dumy !=nullptr)
    {
        cout << " | " << ptr_dumy->GetPID() << " | ";
        ptr_dumy = ptr_dumy->GetNextPointer();
    }
    cout << "\n\n";

    cout << "In Ready Queue: " << endl;
    ProcessControlBlock* ptr_dumy2 = ready_front;
    while (ptr_dumy2 != nullptr)
    {
        cout << " | " << ptr_dumy2->GetPID() << " | ";
        ptr_dumy2 = ptr_dumy2->GetNextPointer();
    }
    cout << "\n\n";

    cout << "In Device Queue: " << endl;
    ProcessControlBlock* ptr_dumy3 = device_front;
    while (ptr_dumy3 != nullptr)
    {
        cout << " | " << ptr_dumy3->GetPID() << " | ";
        ptr_dumy3 = ptr_dumy3->GetNextPointer();
    }
    cout << "\n\n";
    cout << "--------------------------------" << endl;

}

void Scheduler::LoadPCBs(ProcessControlBlock const &pcb)
{
    ProcessControlBlock* ptr_PCB = new ProcessControlBlock(pcb);
    JobPush(*ptr_PCB);
}

bool Scheduler::IsEmpty()const
{
    if (job_length == 0 && ready_length == 0 && device_length == 0)
        return true;
    else
        return false;
}
