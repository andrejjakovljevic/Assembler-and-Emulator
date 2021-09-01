#include "processor.h"
#include "terminal.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    Processor p;
    Terminal t(&p);
    t.start();
    if (argc==1) 
    {
        cout << "Unesite fajl" << endl;
    }
    p.populateMemory(argv[1]);
    p.reg[7] = p.getNumFromAddres(0); // set pc
    do
    {
        p.doInstruction();
        p.checkTimer(); // ako neces timer,otkomenarisi ovo
        t.citaj();
        p.processInterrupts();
        p.printIfNeeded();
    } while (!p.end);
    t.end();
}