#ifndef greater_less_specialized_template_10_16
#define greater_less_specialized_template_10_16
#include "PCB_2.hpp"
#include <functional>
using namespace std;

template <>
struct std::greater<PCB> :public binary_function<PCB, PCB, bool>
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


struct less_than_key
{
	inline bool operator() (const PCB& struct1, const PCB& struct2)
	{
		return (struct1.GetRestTime() < struct2.GetRestTime());
	}
};



#endif // !greater_less_specialized_template_10_16
