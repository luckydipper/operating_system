#include "PCB_2.hpp"
#include "FIFO.hpp"
#include <iostream>
#include <deque>

extern int inner_clock = 0;

using namespace std;

int main()
{
	PCB p1(0, 10);
	PCB p2(3, 12);
	PCB p3(7, 4);
	PCB p4(10, 6);
	PCB p5(14, 8);
	PCB p6(15, 7);
	
	// template specialize test
	less<PCB> Less{};
	cout << Less(p3, p1) << Less(p6, p1) << Less(p5, p4) << endl; // 110


	deque<PCB> process_list{ p1,p2,p3,p4,p5,p6 };
	FIFO scheduling_algorithm{};
	for(const PCB& pcb: process_list)
		scheduling_algorithm.LoadPcb(p1);
	

	return 0;
}