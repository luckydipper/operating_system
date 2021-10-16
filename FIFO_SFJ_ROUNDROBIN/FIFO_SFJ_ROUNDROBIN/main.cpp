// TODO : deque<PCB> process_list{ p1,p2,p3,p4,p5,p6 };
//explicit 하면 이렇게 코딩이 안됨. malloc 쓰면 문제 될 듯. 이동생성자 같은 것으로 극복가능할듯
// 

#include "greater_less_specialized_template.hpp"
#include "PCB_2.hpp"
#include "FIFO.hpp"
#include "SRJF.hpp"
#include <iostream>
#include <deque>

int inner_clock = 0;

using namespace std;

int main()
{
	PCB p1(0, 7);
	PCB p2(2, 4);
	PCB p3(4, 1);
	PCB p4(5, 4);
	PCB p5(14, 8);
	PCB p6(15, 7);

	// template specialize test
	less<PCB> Less{};
	cout << Less(p3, p1) << Less(p6, p1) << Less(p5, p4) << endl; // 110

	
	PCB a1(0, 24); //process 7
	PCB a2(0, 3); // 8
	PCB a3(0, 3); // 9

	//a1,a2,a3
	deque<PCB> process_list{ p1,p2,p3,p4 }; // copy constructor에 explicit 하면 이렇게 코딩이 안됨. malloc 쓰면 문제 될 듯. 이동생성자 같은 것으로 극복가능할듯
	
	FIFO scheduling_algorithm{};
	//scheduling_algorithm.Run();

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