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
	double average_waiting_time; //-1
	int processing_pid; // -1
	bool is_running;
public:
	FIFO();
	void Run();
	bool IsRuning() const;
	//void Dispatch(PCB& pcb);
	void LoadPcb(const PCB& pcb);


	// Level2 API
	void UpdateAverageWaiting(const PCB& pcb); // load, cpu burst 끝날 때. 
	void ShowStatus() const; // Load, cpu burst 끝날 때. 

};


#endif // !__10_16_FIFO_SCHEDULING__
