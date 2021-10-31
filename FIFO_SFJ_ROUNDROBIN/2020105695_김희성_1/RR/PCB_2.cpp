#include "PCB_2.hpp"
#include <iostream>
using namespace std;

int PCB::number_of_PCB = 0;

//PCB::PCB():ARRIVAL_TIME(0), pid(++number_of_PCB)
//{}

PCB::PCB(const int& arrival_time, const int& rest_burst_time) : ARRIVAL_TIME(arrival_time), rest_burst_time(rest_burst_time),pid(++number_of_PCB)
{
    waiting_time = -1;
    should_regist_time = true;
}

PCB::PCB(const PCB& pcb): ARRIVAL_TIME(pcb.ARRIVAL_TIME), rest_burst_time(pcb.rest_burst_time), pid(pcb.pid), waiting_time(pcb.waiting_time), should_regist_time(pcb.should_regist_time){;}

//PCB::PCB(const PCB&& pcb) noexcept : ARRIVAL_TIME(pcb.ARRIVAL_TIME), rest_burst_time(pcb.rest_burst_time), pid(pcb.pid), waiting_time(pcb.waiting_time) { ; }


void PCB::Print() const
{
    cout << "arrival time : " << ARRIVAL_TIME << endl;
    cout << "rest burst time : " << rest_burst_time << endl;
    cout << "waiting : " << waiting_time << endl;
    cout << "PID : " << pid << '\n' << endl;
}

int PCB::GetArrivalTime() const
{
    return ARRIVAL_TIME;
}

int PCB::GetRestTime() const
{
    return rest_burst_time;
}

int PCB::GetPid() const
{
    return pid;
}


void PCB::CpuBurst(const int& time)
{
    rest_burst_time -= time;
    if (rest_burst_time < 0)
        throw std::out_of_range("Burst time should be bigger than 0");
}

void PCB::SetWaitingTime(const int& time)
{
    waiting_time = time;
}


int PCB::GetWaitingTime() const
{
    return waiting_time;
}

bool PCB::ShouldRegistTime() const
{
    return should_regist_time;
}

void PCB::ShouldRegistTime(const bool& setting)
{
    should_regist_time = setting;
}



// operator = 엔 const 한 member 변수를 초기화 할 수 없음. initialize list 처럼. 어떻게 해야하지?
const PCB& PCB::operator= (const PCB& pcb)
{
    ARRIVAL_TIME = pcb.ARRIVAL_TIME;
    rest_burst_time = pcb.rest_burst_time;
    waiting_time = pcb.rest_burst_time;
    pid = pcb.pid;
    should_regist_time = pcb.should_regist_time;
    return *this;
}
