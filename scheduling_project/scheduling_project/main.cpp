#include "scheduler.h" //scheduler �ȿ� PCB ����. 
#include "PCB.h"


int main()
{
    ProcessControlBlock IO_PCB_(Priority::high, true);
    ProcessControlBlock non_IO_PCB_(Priority::middle, false);
    ProcessControlBlock non_IO_PCB_2(Priority::low, false);

    // scheduler() �� �ȵ�? �Լ�ó�� �ؼ� �� �� �ֱ� ������ uniform initialize�� ����Ͽ� �ʱ�ȭ �Ѵ�.
    Scheduler scheduler{};

    // explicit copy �����ڿ� ProcessControlBlock a[2] = {obj1, obj2} �� ��. copy �����ڿ� malloc�� ����߱� ������ �Ϲ������� �Ͼ�� ������.
    //copy constructor�� ���� stack memory�� PBC�� heap����
    scheduler.LoadPCBs(IO_PCB_);
    scheduler.LoadPCBs(non_IO_PCB_);
    scheduler.LoadPCBs(non_IO_PCB_2);

    while(!scheduler.IsEmpty()) // ������ ������ �ǹ��� ���� �̸� ����.
    {
        scheduler.TimeExeption();
        scheduler.LongTermScheduling();
        scheduler.TimeExeption();
        scheduler.ShortTermScheduling();
        scheduler.TimeExeption();
        scheduler.IOScheduling();
    }
    return 0;
}