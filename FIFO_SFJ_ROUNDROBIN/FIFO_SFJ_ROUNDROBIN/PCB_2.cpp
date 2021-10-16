#include "PCB_2.hpp"
#include <iostream>
using namespace std;

int PCB::number_of_PCB = 0;

PCB::PCB(const int& arrival_time, const int& rest_burst_time) : ARRIVAL_TIME(arrival_time), rest_burst_time(rest_burst_time),pid(number_of_PCB)
{
    number_of_PCB++;
    waiting_time = -1;
}

void PCB::Print() const
{
    cout << "arrival time : " << ARRIVAL_TIME << endl;
    cout << "rest burst time : " << rest_burst_time << endl;
    cout << "waiting : " << waiting_time << endl;
    cout << "PID : " << pid << '\n' << endl;
}

int PCB::GetRestTime() const
{
    return rest_burst_time;
}

void PCB::CpuBurst(const int& time)
{
    rest_burst_time -= time;
    if (rest_burst_time < 0)
        throw std::out_of_range("Burst time should be bigger than 0");
}
