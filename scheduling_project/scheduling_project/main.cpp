#include "scheduler.h" //scheduler �ȿ� PCB ����. 
#include "PCB.h"

// time interupt ���� enter�� ����

int main()
{
    ProcessControlBlock IO_PCB_(Priority::high, true);
    ProcessControlBlock non_IO_PCB_(Priority::middle, false);
    Scheduler scheduler;
    // ������ ������. scheduler���� PCB�� new�� delete�� �����ϴ�, push��ŭ pop�� ������ �޸� ������ ��.
    // �����ڿ� �Ҹ��ڰ� �ƴ� �������� new�� delete�� �ϸ� �� �� ��.
    scheduler.PushPCB(IO_PCB_);
    scheduler.PushPCB(IO_PCB_);
    scheduler.PushPCB(IO_PCB_);
    delete scheduler.PopPCB();
    delete scheduler.PopPCB();
    delete scheduler.PopPCB();
    return 0;
}