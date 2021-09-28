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

void Scheduler::TimeInterupt()
{
    // to see what happening
    while (true)
    {
        cout << "Time Interupt!" << endl;
        cout << "Show status : S s" << endl;
        cout << "Continue : C c" << endl;
        
        char input;
        cin >> input;
        switch (input)
        {
        case 's':
//            PrintQueue();
            break;
        case 'S':
//            PrintQueue();
            break;
        case 'c':
            return;
        case 'C':
            return;
        default:
            break;
        }
    }
}

//set status new -> ready
void Scheduler::PushPCB(const ProcessControlBlock &PCB)
{
    ProcessControlBlock* ptr_PCB = new ProcessControlBlock(PCB);
    ptr_PCB->SetStatus(Status::ready);
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
ProcessControlBlock* Scheduler::PopPCB()
{
    ProcessControlBlock* temp = job_rear; 
    job_rear = job_front;
    // -2 because 
    for (int i=0; i < job_length-2; i++) 
        job_rear = job_rear->GetNextPointer();
    job_length--;
    return temp; //new malloc으로 받은 object여서 dangling pointer 안 일어남.
}



