// TODO : deque<PCB> process_list{ p1,p2,p3,p4,p5,p6 };
//explicit 하면 이렇게 코딩이 안됨. malloc 쓰면 문제 될 듯. 이동생성자 같은 것으로 극복가능할듯
// 

#include "PCB_2.hpp"
#include "FIFO.hpp"
#include <iostream>
#include <deque>

extern int inner_clock = 0;

using namespace std;

int main()
{
	PCB p1(0, 10);
	PCB p3(7, 4);
	PCB p4(10, 6);
	PCB p5(14, 8);
	PCB p6(15, 7);
	PCB p2(3, 12);

	// template specialize test
	less<PCB> Less{};
	cout << Less(p3, p1) << Less(p6, p1) << Less(p5, p4) << endl; // 110

	
	deque<PCB> process_list{ p1,p2,p3,p4,p5,p6 }; //explicit 하면 이렇게 코딩이 안됨. malloc 쓰면 문제 될 듯. 이동생성자 같은 것으로 극복가능할듯
	FIFO scheduling_algorithm{};
	for(const PCB& pcb: process_list)
		scheduling_algorithm.LoadPcb(pcb);
	
	scheduling_algorithm;

	return 0;
}