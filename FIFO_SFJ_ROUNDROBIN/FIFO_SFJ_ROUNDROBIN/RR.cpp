#include "FIFO.hpp"
#include <iostream>

extern int inner_clock;

FIFO::FIFO() :average_waiting_time(0), processing_pid(-1), is_running(false)
{}

void FIFO::Run()
{
	is_running = true;
}

void FIFO::Kill()
{
	is_running = false;
}

bool FIFO::IsRuning() const
{
	return is_running;
}

// 1씩 깍아. 처리하고 있는 pid 있으면 기다려.
void FIFO::Dispatch()
{
	//glob clock에 sysnchronize해야 해.
	//processing_pid = PCB_queue.top().GetPid();
	//UpdateAverageWaiting(pcb);

	processing_pid = PCB_queue.top().GetPid();

	if (PCB_queue.size() == 0)
		this->Kill();

	if (PCB_queue.top().GetRestTime() == 0)
	{
		cout << "PID : " << PCB_queue.top().GetPid() << " Complete." << endl;
		PCB_queue.pop();
		ShowStatus();
	}

	//PCB_queue.top().CpuBurst(1);
}

void FIFO::LoadPcb(const PCB& pcb)
{
	PCB_queue.push(pcb);
	ShowStatus();
}

void FIFO::UpdateAverageWaiting(const PCB& pcb)
{
	// 내부 순환 해야하네, 이럴거면 그냥 dequeue 쓸껄 그랬나?
	//	average_waiting_time = ( average_waiting_time + inner_clock ) / PCB_queue.size();
}

void FIFO::ShowStatus() const
{
	priority_queue<PCB, vector<PCB>, greater<PCB>> temp_queue{ PCB_queue };

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


