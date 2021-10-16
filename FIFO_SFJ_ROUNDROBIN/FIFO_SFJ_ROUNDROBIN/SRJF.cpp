#include "SRJF.hpp"
#include <iostream>

extern int inner_clock;

SRJF::SRJF() : sum_waiting_time(0), average_waiting_time(0), num_of_process(0), processing_pid(-1), is_running(false), processing_PCB(PCB(-1, -1))
{
}

void SRJF::Run()
{
	is_running = true;
}

void SRJF::Kill()
{
	is_running = false;
}

bool SRJF::IsRuning() const
{
	return is_running;
}

// 1씩 깍아. 처리하고 있는 pid 있으면 기다려.
void SRJF::Dispatch()
{
	// 모든 process가 끝나도 화면에 출력되도록 함.
	if (PCB_queue.size() == 0)
	{
		ShowStatus();
	}
	//register pid PCB
	processing_pid = PCB_queue.top().GetPid();
	processing_PCB = PCB_queue.top();

	if (processing_PCB.GetRestTime() == 0)
	{
		cout << "PID : " << processing_pid << " Complete." << endl;
		PCB_queue.pop();
		ShowStatus();
		return;
	}

	// 처음 시작 할 때, average wait time을 계산함.
	if (PCB_queue.top().ShouldRegistTime())
	{
		//((PCB)PCB_queue.top()).SetWaitingTime(inner_clock);
		num_of_process++;
		sum_waiting_time += inner_clock;
		average_waiting_time = sum_waiting_time / num_of_process;

		PCB false_should_register{ PCB_queue.top() };
		PCB_queue.pop();

		false_should_register.ShouldRegistTime(false);//////////// 강제 변환 .........하아 observer야... 복사해서 
		processing_PCB.CpuBurst(1);
		false_should_register.CpuBurst(1);
		PCB_queue.push(false_should_register);
		ShowStatus();
		return;
	}

	
	PCB_queue.pop();
	processing_PCB.CpuBurst(1);
	PCB_queue.push(processing_PCB);

 }

void SRJF::LoadPcb(const PCB& pcb)
{
	cout << "PID : " << pcb.GetPid() << " Load!" << endl;
	PCB_queue.push(pcb);
	ShowStatus();
}


void SRJF::ShowStatus() const
{
	priority_queue<PCB, vector<PCB>, greater<PCB>> temp_queue{ PCB_queue };

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
		cout << "|PID : " << temp_queue.top().GetPid() << "| ";
		temp_queue.pop();
	}
	cout << "\naverage waitting time : " << average_waiting_time << endl;

	cout << "\n=====================\n\n" << endl;

	cout << "type 'q' to quit " << endl;
	char interupt;
	cin >> interupt;
	if (interupt == 'q')
		((SRJF*)this)->Kill();
	cout << '\n';
	//cin.clear();
}


