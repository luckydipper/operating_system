#include "PCB_2.hpp"
#include <iostream>
using namespace std;

PCB::PCB(const int& arrival_time, const int& rest_burst_time) : ARRIVAL_TIME(arrival_time), rest_burst_time(rest_burst_time)
{
    waiting_time = -1;
}

void PCB::Print() const
{
    cout << "arrival time : " << ARRIVAL_TIME << endl;
    cout << "rest burst time : " << rest_burst_time << endl;
    cout << "waiting : " << waiting_time << endl;
}

int PCB::GetRestTime() const
{
    return rest_burst_time;
}

void PCB::CpuBurst(const int& time)
{
    rest_burst_time -= time;
}
