// TODO : deque<PCB> process_list{ p1,p2,p3,p4,p5,p6 };
//explicit �ϸ� �̷��� �ڵ��� �ȵ�. malloc ���� ���� �� ��. �̵������� ���� ������ �غ������ҵ�
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
	// ��� ���μ����� �켱������ rest time�� ���� �����ȴ�.
	// rest time�� ���� �ֵ鸸 �ѹ��� �������ش�. 
	PCB p1(0, 10);
	PCB p2(3, 12);
	PCB p3(7, 4);
	PCB p4(10, 6);
	PCB p5(14, 8);
	PCB p6(15, 7);

	//a1,a2,a3
	deque<PCB> process_list{ p1,p2,p3,p4,p5,p6 }; // copy constructor�� explicit �ϸ� �̷��� �ڵ��� �ȵ�. malloc ���� ���� �� ��. �̵������� ���� ������ �غ������ҵ�
	
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