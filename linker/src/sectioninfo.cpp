#include "sectioninfo.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void SectionInfo::addToRelTable(int addend, string symbol, int type, int offset)
{
    rel_table.addEntry(addend,symbol,type,offset);
}

void SectionInfo::set_size(int size)
{
    this->size=size;
}

void SectionInfo::print(ofstream& mf)
{
    const char separator    = ' ';
    const int numWidth      = 10;
    mf << left << setw(numWidth) << setfill(separator) << section_name;
    mf << left << setw(numWidth) << setfill(separator) << size;
    mf << left << setw(numWidth) << setfill(separator) << offset;
    mf << endl;
    rel_table.print(mf);
    mf << "------------------------------------------" << endl;
}