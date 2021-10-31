// TODO : deque<PCB> process_list{ p1,p2,p3,p4,p5,p6 };
//explicit 하면 이렇게 코딩이 안됨. malloc 쓰면 문제 될 듯. 이동생성자 같은 것으로 극복가능할듯
// 

#include "greater_less_specialized_template.hpp"
#include "PCB_2.hpp"
#include "SRJF.hpp"
#include <iostream>
#include <deque>

int inner_clock = 0;

using namespace std;

int main()	
{
	PCB p1(0, 10);
	PCB p2(3, 12);
	PCB p3(7, 4);
	PCB p4(10, 6);
	PCB p5(14, 8);
	PCB p6(15, 7);

	//a1,a2,a3
	deque<PCB> process_list{ p1,p2,p3,p4,p5,p6 }; // copy constructor에 explicit 하면 이렇게 코딩이 안됨. malloc 쓰면 문제 될 듯. 이동생성자 같은 것으로 극복가능할듯
	
	SRJF SRJF_algorithm{};
	SRJF_algorithm.Run();
	while (SRJF_algorithm.IsRuning())
	{
	// Load PCB using arrival time. reset waitting time
		for (PCB& pcb : process_list)
		{
			if (pcb.GetArrivalTime() == inner_clock)
			{
				SRJF_algorithm.LoadPcb(pcb);
			}
		}

		//SortTermScheduling 
		SRJF_algorithm.Dispatch();
		inner_clock++;
	}


	return 0;
}