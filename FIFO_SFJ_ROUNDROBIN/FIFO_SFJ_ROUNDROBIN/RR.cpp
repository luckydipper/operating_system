#include "RR.hpp"
#include <iostream>
#include "greater_less_specialized_template.hpp"
#include <algorithm>

extern int inner_clock;
extern int time_quantum;

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
	
	// 모든 process가 끝나면 종료
	if (PCB_queue.size() == 0)
	{
		ShowStatus();
		if (processing_PCB.GetRestTime() == 0)
		{
			cout << "PID : " << processing_PCB.GetPid() << " Complete." << endl;
			exit(0);
		}
		processing_PCB.CpuBurst(1);
		return;
	}

	if (processing_PCB.GetRestTime() <= 0)
	{
		cout << "PID : " << processing_pid << " Complete." << endl;
		PCB_queue.pop_front();
		ShowStatus();
		return;
	}


	if (processing_PCB.GetRestTime() == 0)
	{
		PCB_queue.erase(std::remove(PCB_queue.begin(), PCB_queue.end(), processing_PCB), PCB_queue.end());
	}

	int processing_index = (inner_clock / time_quantum + 1) % PCB_queue.size();
	processing_PCB = PCB_queue[processing_index];
	processing_PCB.CpuBurst(1);

	if (processing_PCB.ShouldRegistTime())
	{
		//((PCB)PCB_queue.top()).SetWaitingTime(inner_clock);
		num_of_process++;
		sum_waiting_time += (inner_clock - processing_PCB.GetArrivalTime());
		average_waiting_time = sum_waiting_time / num_of_process;
		ShowStatus();
		processing_PCB.ShouldRegistTime(false);
	}


	

}

void RoundRobin::LoadPcb(const PCB& pcb)
{
	cout << "PID : " << pcb.GetPid() << " Load!" << endl;
	PCB_queue.push_back(pcb);
	sort(PCB_queue.begin(), PCB_queue.end(), less_than_key());
}


void RoundRobin::ShowStatus() const
{

	cout << "=====================" << endl;
	cout << "Inner Clock " << inner_clock << endl;

	if (processing_PCB.GetPid() == -1)
	{
		cout << "run Nothing" << endl;
	}
	else
	{
		cout << "PID : " << processing_PCB.GetPid() << " is running!" << endl;
		cout << "Rest burst time : " << processing_PCB.GetRestTime() << endl;
		cout << "\nStatus" << endl;
	}

	for (const PCB& pcb: PCB_queue)
	{
		cout << "|PID : " << pcb.GetPid() << "| ";
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


