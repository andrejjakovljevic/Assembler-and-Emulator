#ifndef SECTIONINFO_HH
#define SECTIONINFO_HH
#include "reallocation_table.h"
#include <map>
#include <vector>
#include <fstream>
using namespace std;

class SectionInfo
{
public:
    string section_name;
    ReallocationTable rel_table;
    int size=0;
    int offset=0;
    vector<unsigned char> myCode;

    SectionInfo(string name, int offset)
    {
        this->section_name=name;
        this->offset=offset;
    }

    void addToRelTable(int addend, string symbol, int type, int offset);
    void set_size(int size);
    void print(ofstream& mf);
};



#endif