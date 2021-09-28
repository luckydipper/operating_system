#ifndef Scheduler_made
#define Scheduler_made

#include "PCB.h"
// Job Queue Ready Queue Device Queue
class Scheduler
{
    // static const int JOB_MAX_LENTH = 16; // ��� ��ü�� ���� ���� �����ؾ� ������ static const
    // static const int READY_MAX_LENTH = 8;
    // static const int DEVICE_MAX_LENTH = 4;
    
    // ProcessControlBlock job_queue[JOB_MAX_LENTH];
    // ProcessControlBlock ready_queue[READY_MAX_LENTH];
    // ProcessControlBlock device_queue[DEVICE_MAX_LENTH];

    ProcessControlBlock *job_front,    *job_rear;
    ProcessControlBlock *ready_front,  *ready_rear;
    ProcessControlBlock *device_front, *device_rear;

    int job_length; // ��ü���� index�� -1�ؼ� ���.
    int ready_length;
    int device_length;

public:
    explicit Scheduler();
    ~Scheduler();

    void TimeExeption();

    //!caution! you must put dynamic allocated PCB
    void JobPush(const ProcessControlBlock& PCB);
    ProcessControlBlock* JobPop();
    void ReadyPush(const ProcessControlBlock& PCB); // status new -> ready
    ProcessControlBlock* ReadyPop();
    void DevicePush(const ProcessControlBlock& PCB); 
    ProcessControlBlock* DevicePop(); // IO true -> false

    void LongTermScheduling(); // Job queue-> ready queue
    void ShortTermScheduling();
    void IOScheduling();
    
    void CpuProcess(const ProcessControlBlock& PCB); // status runing -> terminated 

    void PrintQueue() const; // print Job ready device queue status
    //void SortQueue(); // call Job ready device queue sort
    //void Scheduling(); // update queue

    //Stack to Heap.. malloc Node
    void LoadPCBs(ProcessControlBlock const &pcbs);
    bool IsEmpty()const;
};

#endif //scheduler