#include "driver.h"
#include "parser.h"
#include "sectioninfo.h"
#include <iostream>
#include <fstream>
using namespace std;

driver::driver ()
  : trace_parsing (false), trace_scanning (false)
{
}

void driver::add_to_instructions (Instruction* ins)
{
    instructions.push_back(ins);
    lc+=ins->getSize();
}

void driver::print(ofstream& mf)
{

    const char separator    = ' ';
    const int numWidth      = 10;
    mf << "-------------------SEKCIJE----------------------" << endl;
  for (auto& sekc : section_infos)
  {
    mf << "------------------------------------------" << endl;
    mf << left << setw(numWidth) << setfill(separator) << "Ime";
    mf << left << setw(numWidth) << setfill(separator) << "Velicina";
    mf << left << setw(numWidth) << setfill(separator) << "Offset";
    mf << endl;
    sekc->print(mf);
  }
  mf << "------------------------------------------" << endl;
}

int driver::parse (const std::string &f)
{
  file = f;
  location.initialize (&file);
  scan_begin ();
  yy::parser parser (*this);
  parser.set_debug_level (trace_parsing);
  int res = parser.parse ();
  scan_end ();
  return res;
}

void driver::add_section(string sec_name, int offset)
{
  int predhodni = 0;
  if (section_infos.size()!=0)
  {
    section_infos[section_infos.size()-1]->size=lc;
    predhodni = section_infos[section_infos.size()-1]->offset+section_infos[section_infos.size()-1]->size;
  }
  section_infos.push_back(new SectionInfo(sec_name,predhodni));
  lc=0;
}

void driver::fixLast()
{
  if (section_infos.size()!=0)
  {
    section_infos[section_infos.size()-1]->size=lc;
  }
}


vector<char> driver::secondPass()
{
  vector<char> ukup;
  int loc=0;
  string section="";
  int k=0;
  int local_loc=0;
  for (auto& ins : instructions)
  {
    if (k<(int)section_infos.size() && loc>=section_infos[k]->offset)
    {
      section=section_infos[k]->section_name;
      k++;
      local_loc=0;
    }
    vector<char> v = ins->fix(section_infos, section,local_loc);
    for (int i=0;i<(int)v.size();i++)
    {
      ukup.push_back(v[i]);
    }
    loc+=ins->getSize();
    local_loc+=ins->getSize();
  }
  return ukup;
}


