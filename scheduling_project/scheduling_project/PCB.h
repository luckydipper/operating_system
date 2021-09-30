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

enum class IOStatus
{
    no,
    exist,
    doing,
    done
};

class ProcessControlBlock
{
    static int PCB_num;
    int process_id;
    IOStatus have_IO;
    bool is_in_RAM;
    Priority priority;
    Status state;
    ProcessControlBlock* next_pcb;
    char const environment_variable[256] = { 0 };

public:
    //explicit ProcessControlBlock();
    explicit ProcessControlBlock(const Priority prior, const IOStatus has_IO);
    explicit ProcessControlBlock(const ProcessControlBlock& PCB);
    ~ProcessControlBlock();
    void PrintStatus() const;
    void SetStatus(const Status stat);
    IOStatus HaveIO()const;
    void SetHaveIO(const IOStatus b);
    bool IsInRam()const;
    void SetRamState(const bool b);
    int GetPID()const;
    Priority GetPrior()const;
    void SetPrior(const Priority& p);
    void SetNextPointer(ProcessControlBlock* const ptr_Pcb);
    ProcessControlBlock* GetNextPointer() const;
};

#endif // PCB
