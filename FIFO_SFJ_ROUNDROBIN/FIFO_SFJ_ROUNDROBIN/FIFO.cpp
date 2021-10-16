#include "FIFO.hpp"
#include <iostream>

extern int inner_clock;

//void FIFO::Dispatch(PCB& pcb)
//{
//	//glob clock�� sysnchronize�ؾ� ��.
//	//processing_pid = PCB_queue.top().GetPid();
//
//	while (pcb.GetRestTime() == 0)
//	{
//		pcb.CpuBurst(1);
//	}
//	PCB_queue.pop();
//	ShowStatus();
//}
FIFO::FIFO():average_waiting_time(0), processing_pid(-1), is_running(false)
{}

void FIFO::Run()
{
	is_running = true;
}

bool FIFO::IsRuning() const
{
	return is_running;
}

void FIFO::LoadPcb(const PCB& pcb)
{
	PCB_queue.push(pcb);
	UpdateAverageWaiting(pcb);
	ShowStatus();
}

void FIFO::UpdateAverageWaiting(const PCB& pcb)
{
	average_waiting_time = ( average_waiting_time + pcb.GetWaitingTime() ) / PCB_queue.size();
}

void FIFO::ShowStatus() const
{
	priority_queue<PCB,vector<PCB>,greater<PCB>> temp_queue{ PCB_queue };

	cout << "=====================" << endl;
	cout << "Inner Clock " << inner_clock << endl;
	while (!temp_queue.empty())
	{
		cout << "|PID : " << temp_queue.top().GetPid() << "| ";
		temp_queue.pop();
	}
	cout << "\naverage waitting time : " << average_waiting_time << endl;
	cout << "\n=====================\n\n" << endl;

	char interupt;
	cin >> interupt;
	//cin.clear();
}


