#include "RR.hpp"
#include <iostream>

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
	// 모든 process가 끝나도 화면에 출력되도록 함.
	if (PCB_queue.size() == 0)
	{
		ShowStatus();
		if (processing_PCB.GetRestTime() == 0)
		{
			cout << "PID : " << processing_pid << " Complete." << endl;
			exit(0);
		}

	}
 	int current_index = (inner_clock / time_quantum) % PCB_queue.size();

	int temp = processing_pid;
	processing_pid = PCB_queue[current_index].GetPid();
	processing_PCB = PCB_queue[current_index];
	if (processing_pid != temp)
	{
		cout << "Context switching" << endl;
		ShowStatus();
	}

	//check processing_PCB rest time
	if (processing_PCB.GetRestTime() == 0)
	{
		cout << "PID : " << processing_pid << " Complete." << endl;
		PCB_queue.erase(PCB_queue.begin() + current_index);
		current_index ++;
		ShowStatus();
		return;
	}

	processing_PCB.CpuBurst(1);


	// 처음 시작 할 때, average wait time을 계산함.
	if (processing_PCB.ShouldRegistTime())
	{
		//((PCB)PCB_queue.top()).SetWaitingTime(inner_clock);
		num_of_process++;
		sum_waiting_time += inner_clock;
		average_waiting_time = sum_waiting_time / num_of_process;
		ShowStatus();
	}

	processing_PCB.ShouldRegistTime(false);
	PCB_queue[current_index] = processing_PCB;
}

void RoundRobin::LoadPcb(const PCB& pcb)
{
	cout << "PID : " << pcb.GetPid() << " Load!" << endl;
	PCB_queue.push_back(pcb);
	ShowStatus();
}


void RoundRobin::ShowStatus() const
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
		((RoundRobin*)this)->Kill();
	cout << '\n';
	//cin.clear();
}


