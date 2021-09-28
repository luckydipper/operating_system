#ifndef PCB_HEADER
#define PCB_HEADER
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
    bool have_IO;
    Priority priority;
    Status state;
    ProcessControlBlock* next_pcb;
    char const environment_variable[256] = { 0 };

public:
    //ProcessControlBlock();
    explicit ProcessControlBlock(const Priority prior, const bool has_IO);
    explicit ProcessControlBlock(const ProcessControlBlock& PCB);
    ~ProcessControlBlock();
    void PrintStatus() const;
    void SetStatus(const Status stat);
    bool HaveIO()const;
    Priority GetPrior()const;
    void SetPrior(const Priority& p);
    void SetNextPointer(ProcessControlBlock* const ptr_Pcb);
    ProcessControlBlock* GetNextPointer() const;
};

#endif // PCB
