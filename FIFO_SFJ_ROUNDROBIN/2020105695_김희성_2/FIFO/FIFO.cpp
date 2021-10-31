#include "FIFO.hpp"
#include <iostream>

extern int inner_clock;

FIFO::FIFO(): sum_waiting_time(0),average_waiting_time(0), num_of_process(0), processing_pid(-1), is_running(false),processing_PCB(PCB(-1,-1))
{
}

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

	if (PCB_queue.size() == 0)
	{
		ShowStatus();
		if (processing_PCB.GetRestTime() == 0)
		{
			cout << "PID : " << processing_pid << " Complete." << endl;
			processing_pid = -1;
			exit(0);
		}
	}

	if (processing_pid == -1)
	{

		cout << "PID : " << PCB_queue.front().GetPid() << " Start!" << endl;

		//register pid PCB
		processing_pid = PCB_queue.front().GetPid();
		processing_PCB = PCB_queue.front();

		((PCB)PCB_queue.front()).SetWaitingTime(inner_clock); //////////////////// 강제로 넣음.

		num_of_process++;
		sum_waiting_time += inner_clock - processing_PCB.GetArrivalTime();
		average_waiting_time = sum_waiting_time / num_of_process;

		processing_PCB.CpuBurst(1);
		PCB_queue.pop_front();
		ShowStatus();
		return;
	}
	else if (processing_PCB.GetRestTime() == 0)
	{
		cout << "PID : " << processing_pid << " Complete." << endl;
		processing_pid = -1;
		ShowStatus();
	}
	else
		processing_PCB.CpuBurst(1);
	//PCB_queue.front().CpuBurst(1);
}

void FIFO::LoadPcb(const PCB& pcb)
{
	cout << "PID : " << pcb.GetPid() << " Load!" << endl;
	PCB_queue.push_back(pcb);
	ShowStatus();
}


void FIFO::ShowStatus() const
{
	deque<PCB> temp_queue{ PCB_queue };

	cout << "=====================" << endl;
	cout << "Inner Clock " << inner_clock << endl;
	if (processing_pid == -1)
		cout << "run Nothing" << endl;
	else
	{
		cout << "PID : " << processing_pid << " is running!" << endl;
		cout << "Rest burst time : " << processing_PCB.GetRestTime() << endl;
		cout << "\nStatus" << endl;
	}

	while (!temp_queue.empty())
	{
		cout << "|PID : " << temp_queue.front().GetPid() << "| ";
		temp_queue.pop_front();
	}
	cout << "\naverage waitting time : " << average_waiting_time << endl;

	cout << "\n=====================\n\n" << endl;

	cout << "type 'q' to quit " << endl;
	char interupt;
	cin >> interupt;
	if (interupt == 'q')
		((FIFO*)this)->Kill();
	cout << '\n';
	//cin.clear();
}


