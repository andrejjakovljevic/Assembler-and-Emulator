#ifndef DRIVER_HH
# define DRIVER_HH
# include <string>
# include <map>
# include <vector>
# include "parser.h"
# include "instruction.h"
# include "sectioninfo.h"
# include <fstream>
using namespace std;
// Tell Flex the lexer's prototype ...
# define YY_DECL \
  yy::parser::symbol_type yylex (driver& drv)
// ... and declare it for the parser's sake.
YY_DECL;

// Conducting the whole scanning and parsing of Calc++.
class driver
{
public:
  driver ();

  int lc=0;
  vector<Instruction*> instructions;
  vector<SectionInfo*> section_infos;

  // Run the parser on file F.  Return 0 on success.
  int parse (const std::string& f);
  // The name of the file being parsed.
  std::string file;
  // Whether to generate parser debug traces.
  bool trace_parsing;

  // Handling the scanner.
  void scan_begin ();
  void scan_end ();
  // Whether to generate scanner debug traces.
  bool trace_scanning;
  // The token's location used by the scanner.
  yy::location location;

  void add_to_instructions (Instruction* ins);
  void print(ofstream& mf);
  void add_section(string sec_name, int offset);
  void fixLast();
  void fixIns();
  vector<char> secondPass();
};
#endif // ! DRIVER_HH