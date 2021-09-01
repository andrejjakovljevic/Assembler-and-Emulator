#ifndef TERMINAL_DEFINE
#define TERMINAL_DEFINE
#include "processor.h"

class Terminal
{
public:

    Processor* p;

    Terminal(Processor* _p) : p(_p){};

    void start();
    void end();
    void citaj();

};

#endif