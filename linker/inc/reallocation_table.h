#ifndef REALLOCATIONTABLE_H
#define REALLOCATIONTABLE_H
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class ReallocationTable
{

public:

    struct Entry
    {
        int addend;
        string symbol;
        int type; // 1-dir_16 2-pc_16 3-dir_16(kontra za .word)
        int offset;

        Entry() = default;

        Entry (int addend, string symbol, int type, int offset)
        {
            this->addend=addend;
            this->symbol=symbol;
            this->type=type;
            this->offset=offset;
        }

        void print(ofstream& mf)
        {
            const char separator    = ' ';
            const int numWidth      = 10;
            mf << left << setw(numWidth) << setfill(separator) << addend;
            mf << left << setw(numWidth) << setfill(separator) << symbol;
            mf << left << setw(numWidth) << setfill(separator) << ((type==1)?"DIR_16":((type==2)?"PC_16":"DIR_16_R"));
            mf << left << setw(numWidth) << setfill(separator) << offset;
            mf << endl;
        }

    };

    map<string, vector<Entry> > table;

    void addEntry(int addend, string symbol, int type, int offset);
    vector<Entry> returnEntry(string symbol);
    bool exists(string symbol);
    void print(ofstream& mf);

};










#endif