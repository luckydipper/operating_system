// TODO : deque<PCB> process_list{ p1,p2,p3,p4,p5,p6 };
//explicit �ϸ� �̷��� �ڵ��� �ȵ�. malloc ���� ���� �� ��. �̵������� ���� ������ �غ������ҵ�
// 

#include "PCB_2.hpp"
#include "FIFO.hpp"
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

	// template specialize test
	less<PCB> Less{};
	cout << Less(p3, p1) << Less(p6, p1) << Less(p5, p4) << endl; // 110

	
	deque<PCB> process_list{ p1,p2,p3,p4,p5,p6 }; // copy constructor�� explicit �ϸ� �̷��� �ڵ��� �ȵ�. malloc ���� ���� �� ��. �̵������� ���� ������ �غ������ҵ�
	
	FIFO scheduling_algorithm{};
	scheduling_algorithm.Run();


	while (scheduling_algorithm.IsRuning())
	{

		// Load PCB using arrival time. reset waitting time
		for (PCB& pcb : process_list)
		{
			if (pcb.GetArrivalTime() == inner_clock)
			{
				pcb.SetWaitingTime(inner_clock);
				scheduling_algorithm.LoadPcb(pcb);
			}
		}



		inner_clock++;
	}


	return 0;
}