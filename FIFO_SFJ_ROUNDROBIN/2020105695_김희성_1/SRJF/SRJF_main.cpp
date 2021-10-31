// TODO : deque<PCB> process_list{ p1,p2,p3,p4,p5,p6 };
//explicit �ϸ� �̷��� �ڵ��� �ȵ�. malloc ���� ���� �� ��. �̵������� ���� ������ �غ������ҵ�
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
	PCB p1(0, 7);
	PCB p2(2, 4);
	PCB p3(4, 1);
	PCB p4(5, 4);

	//a1,a2,a3
	deque<PCB> process_list{ p1,p2,p3,p4 }; // copy constructor�� explicit �ϸ� �̷��� �ڵ��� �ȵ�. malloc ���� ���� �� ��. �̵������� ���� ������ �غ������ҵ�
	
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