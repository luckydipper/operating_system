// TODO : Pop and Push from job queue ������ �����. �ߺ� ����
// TODO : Next�� ����Ű�� pointer, �� Node ���� pointer�� ��� �����Ҵ� �ؾ��� �� ����. �����Ѱ�? new�� �����ڸ� ȣ���ϴµ� ������ �ȿ��� �����ڸ� ȣ���ϴ°�?
// TODO : ���� ������ �ȿ� pointer�� new�� ���ٸ�, ���� �����ڿ� new�� �ؼ� stack�� �ִ� ��ü�� heap���� �����;��� ������ �ֳ�?
// TODO : reference�� return�� parameter�� ����. ������ iteration�� �ȵǴ�, �̶� pointer�� ����.
// QUEUE�� ���� �����س��� JOB READY DEVICE ������...
// Load PCB���� �����Ҵ��� �ѹ��� ������
// CPU���� ���� free
// ó�� ������ �� stack pop�� �����ع���
        //ProcessControlBlock* temp = ready_rear;
        //ready_rear = ready_front;
        //// -2 because 
        //for (int i = 0; i < ready_length - 2; i++)
        //    ready_rear = ready_rear->GetNextPointer();
        //ready_length--;
        //return temp; //new malloc���� ���� object���� dangling pointer �� �Ͼ.
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
// ����� ������ ���� �ʾ���..
ProcessControlBlock* Scheduler::JobPop()
{
    ProcessControlBlock* temp = job_front;  //reference�� ��ٸ�? job front�� �ٲ�鼭 ���� �ٲ������? iteration �� �� ��?
    
    while (temp->IsInRam())
    {
        if (temp == nullptr)
            return job_front;
        temp = temp->GetNextPointer();
    };
    //���⼭ return �Ұ� copy���ָ�, ready push���� copy �Ұ�.
    return temp; // dangling pointer �� �Ͼ??? object ���� ���� ���� pointer�� new malloc���� ���� object
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
    return temp; //new malloc���� ���� object���� dangling pointer �� �Ͼ.
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
    return temp; //new malloc���� ���� object���� dangling pointer �� �Ͼ.
}

// Job-> ready
void Scheduler::LongTermScheduling()
{
    if (job_length == 0)
        return;
    //ReadyPush(*JobPop()); �ٷ� ������ �ӽð�ü
    ProcessControlBlock* temp = JobPop();
    //ProcessControlBlock copied_PCB{ *temp }; //copy construction dynamic allocation //������ ��ü�� return �Ѵ�.
    ProcessControlBlock* copied_PCB = new ProcessControlBlock(*temp);
    copied_PCB->SetNextPointer(nullptr);
    ReadyPush(*copied_PCB); // ���⼭ �ٷ� ������.  //���ʿ� ������ ȣ���ϴ°� 
}
//new�� stack���� ���� ���ö� delete ���ݾ�? stack 2���� �����Ǵ� ���� �ƴϾ�. 

void Scheduler::ShortTermScheduling()
{
    if (ready_length == 0)
        return;
    ProcessControlBlock* from_ready = ReadyPop(); // ��ü�� �������� �ʾ� �Ҹ��ڰ� ȣ����� ����.
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
