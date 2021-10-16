#ifndef __10_16_FIFO_SCHEDULING__
#define __10_16_FIFO_SCHEDULING__
#include <queue>
#include "PCB_2.hpp"
#include <functional>
using namespace std;
//template specialization

template <>
struct std::greater<PCB> //:public binary_function<PCB, PCB, bool>
{
	bool operator() (const PCB& left, const PCB& right) const
	{
		return left.GetRestTime() > right.GetRestTime();
	}
};

template <>
struct std::less<PCB> :public binary_function<PCB, PCB, bool>
{
	bool operator() (const PCB& left, const PCB& right) const
	{
		return left.GetRestTime() < right.GetRestTime();
	}
};


class FIFO
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
	FIFO();
	void Run();
	void Kill();
	bool IsRuning() const;
	void Dispatch();
	void LoadPcb(const PCB& pcb);


	// Level2 API
	void ShowStatus() const; // Load, cpu burst ³¡³¯ ¶§. 

};


#endif // !__10_16_FIFO_SCHEDULING__
