#ifndef PROCESSOR_DEFINE
#define PROCESSOR_DEFINE
#include <string>
#include <queue>
#include <chrono>
using namespace std;

class Processor
{
public:
    unsigned char mem[1<<16] = {0}; // memorija
    bool interrupts[8] = {0};
    int num_ivt_ulaza=8;
    unsigned short reg[9] = {0};
    //unsigned short psw;
    int mask_z=0;
    int mask_o=1;
    int mask_c=2;
    int mask_n=3;
    int mask_tr=13;
    int mask_tl=14; 
    int mask_i=15;
    bool end=false;
    bool is_in_interrupt=false;
    chrono::time_point<chrono::high_resolution_clock> lastTime;

    Processor();

    short getNumFromAddres(int pos)
    {
        return ((mem[pos+1]<<8)|mem[pos]);
    }

    void populateMemory(string filename);

    unsigned short findStart();

    void doInstruction();

    unsigned char takeNext();

    unsigned short findVal(unsigned char drugi_bajt,unsigned char bajtic);

    void push(unsigned short val);

    unsigned short pop();

    void wrongOpCode();

    void processInterrupts();

    void checkTimer();

    void printIfNeeded();
};


#endif