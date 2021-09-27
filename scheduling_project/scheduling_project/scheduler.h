#ifndef Scheduler_made
#define Scheduler_made

#include "PCB.h"
// Job Queue Ready Queue Device Queue
class Scheduler
{
    static const int JOB_MAX_LENTH = 16; // ��� ��ü�� ���� ���� �����ؾ� ������ static const
    static const int READY_MAX_LENTH = 8;
    static const int DEVICE_MAX_LENTH = 4;

    ProcessControlBlock job_queue[JOB_MAX_LENTH];
    ProcessControlBlock ready_queue[READY_MAX_LENTH];
    ProcessControlBlock device_queue[DEVICE_MAX_LENTH];

    int job_;

public:
    explicit Scheduler();
    ~Scheduler();
    void PrintQueue() const; // call Job ready device queue status
    void SortQueue(); // call Job ready device queue sort
    void Scheduling(); // update queue
};

// 16 PCB capacity
class JobQueue 
{
    ProcessControlBlock* front;
    ProcessControlBlock* back;
    int length;
public:
    static int GetPCBCount(); //call by reference ó�� ���� �״�� return ��
};

// 8 PCB capacity
class ReadyQueue
{
    static int num_of_process;
public:
    static int GetPCBCount(); //call by reference ó�� ���� �״�� return ��
};

// 16 PCB capacity
class DevideQueue
{
    static int num_of_process;
public:
    static int GetPCBCount(); //call by reference ó�� ���� �״�� return ��
};

#endif //scheduler