// TODO : Pop and Push from job queue 구조가 비슷함. 중복 제거
// TODO : Next를 가르키는 pointer, 즉 Node 안의 pointer는 모두 동적할당 해야할 것 같다. 가능한가? new는 생성자를 호출하는데 생성자 안에서 생성자를 호출하는게?
// TODO : 만약 생성자 안에 pointer에 new가 들어간다면, 복사 생성자에 new를 해서 stack에 있는 객체를 heap으로 가져와야할 이유가 있나?
// TODO : reference는 return과 parameter에 쓰자. 하지만 iteration은 안되니, 이땐 pointer를 쓰자.
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
#include <assert.h>
#include "scheduler.h"
#include <iostream>
#include <stdbool.h>
using namespace std;


Scheduler::Scheduler() : job_length(0), ready_length(0), device_length(0),
job_front(nullptr), job_rear(nullptr),
ready_front(nullptr), ready_rear(nullptr),
device_front(nullptr), device_rear(nullptr)
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
    ProcessControlBlock* temp = job_front;  //reference를 썼다면? job front가 바뀌면서 같이 바뀌었겠지? iteration 안 될 듯?
    
    while (temp->IsInRam())
    {
        if (temp == nullptr)
            return job_front;
        temp = temp->GetNextPointer();
    };
    //여기서 return 할것 copy해주면, ready push에서 copy 불가.
    return temp; // dangling pointer 안 일어남??? object 안의 값을 가진 pointer나 new malloc으로 받은 object
}

// change status ready
void Scheduler::ReadyPush(ProcessControlBlock& PCB)
{
    //already in ReadyQueue
    if (PCB.IsInRam() && PCB.HaveIO()!= IOStatus::done)
        return;

    PCB.SetStatus(Status::ready);
    PCB.SetRamState(true);
    ProcessControlBlock* ptr_PCB = &PCB;
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
    temp->SetHaveIO(IOStatus::done);
    return temp; //new malloc으로 받은 object여서 dangling pointer 안 일어남.
}

// Job-> ready
void Scheduler::LongTermScheduling()
{
    if (job_length == 0)
        return;
    //ReadyPush(*JobPop()); 바로 넣으면 임시객체
    ProcessControlBlock* temp = JobPop();
    //ProcessControlBlock copied_PCB{ *temp }; //copy construction dynamic allocation //생성된 객체를 return 한다.
    ProcessControlBlock* copied_PCB = new ProcessControlBlock(*temp);
    copied_PCB->SetNextPointer(nullptr);
    ReadyPush(*copied_PCB); // 여기서 바로 해제됨.  //애초에 생성자 호출하는게 
}
//new는 stack에서 빠져 나올때 delete 되잖아? stack 2개라서 해제되는 것은 아니야. 

void Scheduler::ShortTermScheduling()
{
    if (ready_length == 0)
        return;
    ProcessControlBlock* from_ready = ReadyPop(); // 객체를 생성하지 않아 소멸자가 호출되지 않음.
    CpuProcess(*from_ready);
}

//change IO status
void Scheduler::IOScheduling()
{
    if (device_length == 0)
        return;
    ReadyPush(*DevicePop());
}

void Scheduler::CpuProcess(ProcessControlBlock& PCB)
{
    cout << "Process PID : " << PCB.GetPID() << " Runing." << endl;

    if (PCB.HaveIO()==IOStatus::exist)
    {
        cout << "Process PID : " << PCB.GetPID() << " has IO." << endl;
        DevicePush(PCB);
    }
    else
    {
        DeleteJobQueueItem(PCB); // Delete PCB in queue
        delete& PCB;
    }
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

void Scheduler::DeleteJobQueueItem(ProcessControlBlock& PCB)
{
    ProcessControlBlock* iterator = job_front;
    while (iterator != nullptr)
    {
        if (iterator == &PCB)
        {
            ProcessControlBlock* temp_del = iterator;
            iterator = iterator->GetNextPointer();
            delete temp_del;
            return;
        }
        iterator = iterator->GetNextPointer();
    }
    assert(true);//memorry leak
}
