#ifndef __10_16_PCB__
#define __10_16_PCB__

class PCB
{
private:
    const int ARRIVAL_TIME;
    int rest_burst_time;
    int waiting_time;
    static int number_of_PCB;
    const int pid;
public:
    explicit PCB(const int& arrival_time, const int& rest_burst_time);
    //PCB(const PCB& copied); use default copy constructor
    void Print() const; 
    int GetArrivalTime() const;
    int GetRestTime() const;
    int GetPid() const;

    void CpuBurst(const int& time);
    void SetWaitingTime(const int& time);

    void operator= (const PCB& pcb);
};

#endif // !__10_16_PCB__

