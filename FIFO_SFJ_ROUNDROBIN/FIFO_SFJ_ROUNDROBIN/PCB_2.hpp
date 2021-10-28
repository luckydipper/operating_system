#ifndef __10_16_PCB__
#define __10_16_PCB__

class PCB
{
private:
    int ARRIVAL_TIME; //default constructor assignment operator���� constrol �Ұ���. STl���� default constructor�� �־�� �� �� ����. const
    int rest_burst_time;
    int waiting_time;
    static int number_of_PCB;
    int pid; //const
    bool should_regist_time; // SJF param
public:
    //explicit PCB();
    explicit PCB(const int& arrival_time, const int& rest_burst_time);
    PCB(const PCB& pcb); //explicit
    //explicit PCB(const PCB&& pcb) noexcept;
    //PCB(const PCB& copied); use default copy constructor
    void Print() const; 
    int GetArrivalTime() const;
    int GetRestTime() const;
    int GetPid() const;

    void CpuBurst(const int& time);
    void SetWaitingTime(const int& time);
    int GetWaitingTime() const;
    bool ShouldRegistTime() const;
    void ShouldRegistTime(const bool& setting);

    // STL�� ���� ��ü�� operator =�� ������
    const PCB& operator= (const PCB& pcb);

    const bool operator ==(const PCB& pcb);
};

#endif // !__10_16_PCB__

