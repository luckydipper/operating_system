#include "scheduler.h" //scheduler 안에 PCB 있음. 
#include "PCB.h"


int main()
{
    ProcessControlBlock IO_PCB_(Priority::high, true);
    ProcessControlBlock non_IO_PCB_(Priority::middle, false);
    ProcessControlBlock non_IO_PCB_2(Priority::low, false);

    // scheduler() 왜 안됨? 함수처럼 해석 될 수 있기 때문에 uniform initialize를 사용하여 초기화 한다.
    Scheduler scheduler{};

    // explicit copy 생성자에 ProcessControlBlock a[2] = {obj1, obj2} 안 됨. copy 생성자에 malloc을 사용했기 때문에 암묵적으로 일어나면 위험함.
    //copy constructor를 통해 stack memory의 PBC를 heap으로
    scheduler.LoadPCBs(IO_PCB_);
    scheduler.LoadPCBs(non_IO_PCB_);
    scheduler.LoadPCBs(non_IO_PCB_2);

    while(!scheduler.IsEmpty()) // 다음엔 긍정인 의미의 변수 이름 쓰기.
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