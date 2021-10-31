// TODO : deque<PCB> process_list{ p1,p2,p3,p4,p5,p6 };
//explicit 하면 이렇게 코딩이 안됨. malloc 쓰면 문제 될 듯. 이동생성자 같은 것으로 극복가능할듯
// 
#include "greater_less_specialized_template.hpp"
#include "PCB_2.hpp"
#include "RR.hpp"
#include <iostream>
#include <deque>

int inner_clock = 0;
int time_quantum = 3;
using namespace std;

int main()
{
	// 모든 프로세스의 우선순위는 rest time에 따라 결정된다.
	// rest time이 같은 애들만 한번씩 실행해준다. 
	PCB p1(0, 10);
	PCB p2(3, 12);
	PCB p3(7, 4);
	PCB p4(10, 6);
	PCB p5(14, 8);
	PCB p6(15, 7);

	//a1,a2,a3
	deque<PCB> process_list{ p1,p2,p3,p4,p5,p6 }; // copy constructor에 explicit 하면 이렇게 코딩이 안됨. malloc 쓰면 문제 될 듯. 이동생성자 같은 것으로 극복가능할듯
	
	RoundRobin RoundRobin_algorithm{};
	RoundRobin_algorithm.Run();
	while (RoundRobin_algorithm.IsRuning())
	{
		// Load PCB using arrival time. reset waitting time
		for (PCB& pcb : process_list)
		{
			if (pcb.GetArrivalTime() == inner_clock)
			{
				RoundRobin_algorithm.LoadPcb(pcb);
			}
		}

		//SortTermScheduling 
		if(inner_clock % time_quantum)
			RoundRobin_algorithm.Dispatch();
		inner_clock++;
	}


	return 0;
}