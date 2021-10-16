#include "RR.hpp"
#include <iostream>

extern int inner_clock;

RoundRobin::RoundRobin() : sum_waiting_time(0), average_waiting_time(0), num_of_process(0), processing_pid(-1), is_running(false), processing_PCB(PCB(-1, -1))
{
}

void RoundRobin::Run()
{
	is_running = true;
}

void RoundRobin::Kill()
{
	is_running = false;
}

bool RoundRobin::IsRuning() const
{
	return is_running;
}

// 1씩 깍아. 처리하고 있는 pid 있으면 기다려.
void RoundRobin::Dispatch()
{
	//glob clock에 sysnchronize해야 해.
	//processing_pid = PCB_queue.top().GetPid();
	//UpdateAverageWaiting(pcb);


	if (PCB_queue.size() == 0)
	{
		ShowStatus();
	}


	if (processing_pid == -1)
	{

		cout << "PID : " << PCB_queue.top().GetPid() << " Start!" << endl;

		//register pid PCB
		processing_pid = PCB_queue.top().GetPid();
		processing_PCB = PCB_queue.top();

		((PCB)PCB_queue.top()).SetWaitingTime(inner_clock); //////////////////// 강제로 넣음.

		num_of_process++;
		sum_waiting_time += inner_clock;
		average_waiting_time = sum_waiting_time / num_of_process;

		processing_PCB.CpuBurst(1);
		PCB_queue.pop();
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
	//PCB_queue.top().CpuBurst(1);
}

void RoundRobin::LoadPcb(const PCB& pcb)
{
	PCB_queue.push(pcb);
	ShowStatus();
}


void RoundRobin::ShowStatus() const
{
	priority_queue<PCB, vector<PCB>, greater<PCB>> temp_queue{ PCB_queue };

	cout << "=====================" << endl;
	cout << "Inner Clock " << inner_clock << endl;
	if (processing_pid == -1)
		cout << "run Nothing" << endl;
	else
		cout << "PID : " << processing_pid << " is running!" << endl;

	while (!temp_queue.empty())
	{
		cout << "|PID : " << temp_queue.top().GetPid() << "| ";
		temp_queue.pop();
	}
	cout << "\naverage waitting time : " << average_waiting_time << endl;

	cout << "\n=====================\n\n" << endl;

	cout << "type 'q' to quit " << endl;
	char interupt;
	cin >> interupt;
	if (interupt == 'q')
		((RoundRobin*)this)->Kill();
	cout << '\n';
	//cin.clear();
}


