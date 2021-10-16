#include "FIFO.hpp"
#include <iostream>


//void FIFO::Dispatch(PCB& pcb)
//{
//	//glob clock에 sysnchronize해야 해.
//	//processing_pid = PCB_queue.top().GetPid();
//
//	while (pcb.GetRestTime() == 0)
//	{
//		pcb.CpuBurst(1);
//	}
//	PCB_queue.pop();
//	ShowStatus();
//}

void FIFO::LoadPcb(const PCB& pcb)
{
	PCB_queue.push(pcb);
	ShowStatus();
}

void FIFO::ShowStatus() const
{
	priority_queue<PCB,vector<PCB>,greater<PCB>> temp_queue{ PCB_queue };

	cout << "=====================" << endl;
	while (!temp_queue.empty())
	{
		cout << " |PID : " << temp_queue.top().GetPid() << "| ";
		temp_queue.pop();
	}
	cout << "\n=====================\n\n" << endl;

	//char interupt;
	//cin >> interupt;
	//cin.clear();
}
