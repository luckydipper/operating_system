#ifndef PCB
#define PCB
enum class Status
{
    new_,
    ready,
    running,
    waitting,
    terminate
};

enum class Priority
{
    low,
    middle,
    high
};

class ProcessControlBlock
{
    static int PCB_num;
    const int process_id;
    Priority priority;
    Status state;
    ProcessControlBlock* next_pcb;
    char const environment_variable[256] = { 0 }; 

public:
    ProcessControlBlock();
    explicit ProcessControlBlock(const Priority prior);
    ~ProcessControlBlock();
    void PrintStatus() const;
    void SetPointer(ProcessControlBlock* ptr_Pcb);
};

#endif // PCB
