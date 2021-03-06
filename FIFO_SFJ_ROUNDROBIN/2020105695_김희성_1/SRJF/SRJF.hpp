#ifndef __10_16_SRJF_SCHEDULING__
#define __10_16_SRJF_SCHEDULING__
#include <queue>
#include "PCB_2.hpp"
#include "greater_less_specialized_template.hpp"
using namespace std;
//template specialization

class SRJF
{
private:
	priority_queue<PCB, vector<PCB>, greater<PCB>> PCB_queue;
	int sum_waiting_time;
	int num_of_process;
	double average_waiting_time; //-1
	int processing_pid; // -1
	PCB processing_PCB;
	bool is_running;
public:
	SRJF();
	void Run();
	void Kill();
	bool IsRuning() const;
	void Dispatch();
	void LoadPcb(const PCB& pcb);

	// Level2 API
	void ShowStatus() const; // Load, cpu burst ???? ??. 

};


#endif // !__10_16_FIFO_SCHEDULING__
