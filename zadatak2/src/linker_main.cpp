#include <iostream>
#include "symboltable.h"
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <vector>
#include "linker_input.h"
using namespace std;

extern vector<string> split(const string& str, const string& delim);

void printLinkerOutput(ofstream& myfile,LinkerInput& linkerInput)
{
    linkerInput.st.print(myfile);
    const char separator    = ' ';
    const int numWidth      = 10;
    myfile << "-------------------SEKCIJE----------------------" << endl;
    for (auto& sekc : linkerInput.si)
    {
        myfile << "------------------------------------------" << endl;
        myfile << left << setw(numWidth) << setfill(separator) << "Ime";
        myfile << left << setw(numWidth) << setfill(separator) << "Velicina";
        myfile << left << setw(numWidth) << setfill(separator) << "Offset";
        myfile << endl;
        sekc.print(myfile);
    }
    myfile << "------------------------------------------" << endl;
    myfile << "----------IZGLED PROGRAMA---------------" << endl;
    for (auto&  si_info : linkerInput.si)
    {
        for (int i=0;i<(int)si_info.myCode.size();i++)
        {
        myfile << right << hex << setfill('0') << setw(2) << uppercase << +(unsigned char)(si_info.myCode[i]);
        myfile << " ";
        }
        myfile << endl;
    }
    myfile << std::dec;
    myfile << "-----------------------" << endl;
    myfile.close();
}

int main(int argc, char *argv[])
{
    string ulaz="";
    string izlaz="l.o";
    bool jel_izlaz=false;
    bool is_hex=false;
    bool is_linkable=false;
    map<string,long> places;
    vector<LinkerInput> liVector;
    vector<string> fileNames;
    for (int i=1;i<argc;i++)
    {
        if (string(argv[i])=="-o")
        {
            jel_izlaz=true;
        }
        else if (jel_izlaz)
        {
            izlaz=argv[i];
            jel_izlaz=false;
        }
        else if (string(argv[i])=="-hex") is_hex=true;
        else if (string(argv[i])=="-linkable") is_linkable=true;
        else if (argv[i][0]=='-')
        {
            string k=argv[i];
            vector<string> pom = split(k,"=");
            vector<string> pompom=split(pom[1],"@");
            string name = pompom[0];
            string size = pompom[1];
            long pos = (long)(strtol(size.c_str(),nullptr,0));
            places[name]=pos;
        }
        else fileNames.push_back(argv[i]); 
    }
    for (int i=0;i<(int)fileNames.size();i++)
    {
        LinkerInput li(fileNames[i]);
        liVector.push_back(li);
    }
    if (is_hex && is_linkable) 
    {
        cout << "Can't be hex and linkable" << endl;
        return -1;
    }
    if (!is_hex && !is_linkable)
    {
        cout << "Can't be neihter hex nor linkable" << endl;
        return -1;
    }
    if (liVector.size()==0)
    {
        cout << "Enter files" << endl;
        return -1;
    }
    if (is_linkable) places.clear();
    for (int i=1;i<(int)liVector.size();i++)
    {
        liVector[0].mergeLinkerInputs(liVector[i]);
    }
    ofstream myfile;
    myfile.open(izlaz);
    if (is_linkable)
    {
        printLinkerOutput(myfile,liVector[0]);
        return 0;
    }
    liVector[0].checkIsOkay(places); // proveri jel ima preklapanja
    liVector[0].fixStarts(places); // sredi startove
    liVector[0].fixReallocation(); // sredi relokacije
    liVector[0].dumpHex(myfile);
    myfile.close();
    return 0;
}