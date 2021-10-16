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
	p1.Print();
	less<PCB> Less{};
	cout << Less(p3, p1); // 1
	cout << Less(p6, p1); // 1
	cout << Less(p5, p4); // 0

	return 0;
}