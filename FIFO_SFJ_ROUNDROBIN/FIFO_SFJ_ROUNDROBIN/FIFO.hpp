#ifndef __10_16_FIFO_SCHEDULING__
#define __10_16_FIFO_SCHEDULING__
#include <queue>
#include "PCB_2.hpp"
#include <functional>
using namespace std;
//template specialization

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
	const int initial_size;
	priority_queue<PCB, vector<PCB>, less<PCB>> PCB_queue;
public:
	//FIFO();
	//Run(); -> while 
	//ShowStatus()
};


#endif // !__10_16_FIFO_SCHEDULING__
