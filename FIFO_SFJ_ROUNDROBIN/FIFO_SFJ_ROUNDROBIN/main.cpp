#include "PCB_2.hpp"
#include "FIFO.hpp"
#include <functional>
#include <iostream>
// synchronize 
int inner_clock = 0;
using namespace std;

int main()
{
	PCB p1(0, 10);
	PCB p2(3, 12);
	PCB p3(7, 4);
	PCB p4(10, 6);
	PCB p5(14, 8);
	PCB p6(15, 7);
	PCB pcb_list[] = { p1,p2,p3,p4,p5,p6 };
	
	less<PCB> Less{};
	cout << Less(p3, p1) << Less(p6, p1) << Less(p5, p4) << endl; // 110

	p1.Print();
	p1.CpuBurst(10);
	p1.Print();


	return 0;
}