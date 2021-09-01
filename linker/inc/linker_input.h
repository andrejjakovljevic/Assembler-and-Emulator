#ifndef LINKER_INPUT_HH
#define LINKER_INPUT_HH
#include "symboltable.h"
#include "sectioninfo.h"
#include <vector>
using namespace std;
class LinkerInput
{
public:
    SymbolTable st;
    vector<SectionInfo> si;
    vector<unsigned char> code;

    LinkerInput(string filename);
    void mergeLinkerInputs(LinkerInput l1);
    int findSizeOfSecition(string section);
    int getSectionInfoPos(string section);
    void checkIsOkay(map<string,long>& places);
    void fixStarts(map<string,long>& places);
    void dumpHex(ofstream& myfile);
    void fixReallocation();
};

#endif