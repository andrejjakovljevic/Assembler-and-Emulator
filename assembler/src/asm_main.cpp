#include <iostream>
#include "driver.h"
#include "symboltable.h"
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int main (int argc, char *argv[])
{
  driver drv;
  string ulaz="";
  string izlaz="a.o";
  bool jel_izlaz=false;
  for (int i = 1; i < argc; i++)
  {
    if (argv[i] == string ("-o"))
    {
      jel_izlaz=true;
    }
    else if (jel_izlaz)
    {
      izlaz=argv[i];
      jel_izlaz=false;
    }
    else ulaz = argv[i];
  }
  drv.parse(ulaz);
  ofstream myfile;
  myfile.open (izlaz);
  SymbolTable* simtab = SymbolTable::getOnlySymbolTable();
  vector<char> ins = drv.secondPass();
  simtab->print(myfile);
  drv.print(myfile);
  myfile << "----------IZGLED PROGRAMA---------------" << endl;
  for (auto&  si_info : drv.section_infos)
  {
    for (int i=0;i<(int)si_info->myCode.size();i++)
    {
      myfile << right << hex << setfill('0') << setw(2) << uppercase << +(unsigned char)(si_info->myCode[i]);
      myfile << " ";
    }
    myfile << endl;
  }
  myfile << std::dec;
  myfile << "-----------------------" << endl;

  myfile.close();
  return 0;
}