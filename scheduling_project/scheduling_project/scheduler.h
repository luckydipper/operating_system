#ifndef Scheduler_made
#define Scheduler_made

#include "PCB.h"
// Job Queue Ready Queue Device Queue
class Scheduler
{
    ProcessControlBlock *job_front,    *job_rear;
    ProcessControlBlock *ready_front,  *ready_rear;
    ProcessControlBlock *device_front, *device_rear;

    int job_length; // 전체길이 index는 -1해서 사용.
    int ready_length;
    int device_length;

public:
    explicit Scheduler();
    ~Scheduler();

    // LEVLE1 API
    void LongTermScheduling(); // Job queue-> ready queue
    void ShortTermScheduling();
    void IOScheduling();
    void TimeExeption();
    void LoadPCBs(ProcessControlBlock const& pcbs); //Stack to Heap.. malloc Node
    bool IsEmpty()const;
    //void SortQueue(); // call Job ready device queue sort

    // LEVEL2 API
    //!caution! you must put dynamic allocated PCB
    void JobPush(const ProcessControlBlock& PCB);
    ProcessControlBlock* JobPop(); //If PCB hasn't dispatched, Job QUEUE not deleted. 

    void ReadyPush(ProcessControlBlock& PCB); //PCB status chagne, new -> ready, is_in_ram -> true
    ProcessControlBlock* ReadyPop();
    void DevicePush(const ProcessControlBlock& PCB); 
    ProcessControlBlock* DevicePop(); // IO true -> false
    void CpuProcess(ProcessControlBlock& PCB); //free PCB, call DeleteJobQueueItem 
    void PrintQueue() const; // print Job ready device queue status

    // LEVEL3 API
    void DeleteJobQueueItem(ProcessControlBlock& PCB); //free PCB

};

#endif //scheduler