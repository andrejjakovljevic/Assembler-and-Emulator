%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.1"
%defines

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
  #include <string>
  #include "instruction.h"
  #include "symboltable.h"
  #include "error.h"
  #include "string.h"
  class driver;
  using namespace std;
}

// The parsing context.
%param { driver& drv }

%locations

%define parse.trace
%define parse.error verbose

%code {
#include "driver.h"
#include <iostream>
}

%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
  PLUS    "+"
  STAR    "*"
  LPAREN  "["
  RPAREN  "]"
  COLON ":"
  COMMA ","
  DOLAR "$"
  PERCENT "%"
  GLOBAL
  EXTERN
  SECTION
  EQU
;

%token <int> DECIMAL
%token <int> HEX
%token <std::string> WORD
%token <std::string> SKIP
%token <std::string> SYMBOL
%token <std::string> REG
%token <std::string> EMPTYINS
%token <std::string> JMPINS
%token <std::string> ONEINS
%token <std::string> TWOINS
%token <std::string> LDRSTRINS
%token <std::string> NOTINS
%type <Instruction*> instruction
%type <int> literal
%type <Operand*> operand_arithm
%type <Operand*> operand_jump
%type <Operand*> operand_reg
%type <std::vector<std::string>*> list_of_symbols
%type <std::vector<std::string>*> list_of_only_symbols
%printer { yyoutput << $$; } <*>;

%%

%start program_start;
program_start:
  program {};

program:
  header sections end_program {};

sections:
  %empty {}
  | sections section {};

header:
  %empty {}
  | header equ_directive {}
  | header global_directive {}
  | header extern_directive {}

section:
  section_begining instructions {};

instructions:
  %empty {}
  | instructions line {};

line:
  instruction {}
  | label {}
  | global_directive {}
  | extern_directive {}
  | equ_directive {};

section_begining:
  SECTION SYMBOL 
  {
    drv.add_section($2,drv.lc);
    SymbolTable* primerak = SymbolTable::getOnlySymbolTable();
    primerak->addSection($2);
  };

end_program:
  END {drv.fixLast(); return 0;};

label:
  SYMBOL ":" 
  {
    SymbolTable* primerak = SymbolTable::getOnlySymbolTable();
    if (primerak->exists($1))
    {
      if (!primerak->undefined($1)) throw yy::parser::syntax_error(drv.location,"Already defined");
    }
    primerak->addEntry($1, drv.section_infos[drv.section_infos.size()-1]->section_name, drv.lc);
  }

equ_directive:
  EQU SYMBOL "," literal 
  {
    SymbolTable* primerak = SymbolTable::getOnlySymbolTable();
    if (primerak->exists($2))
    {
      if (!primerak->undefined($2)) throw yy::parser::syntax_error(drv.location,"Already defined");
    }
    primerak->addEntry($2, "abs", $4);
  };

extern_directive:
  EXTERN list_of_symbols 
  {
    SymbolTable* primerak = SymbolTable::getOnlySymbolTable();
    for (string& simbol : (*$2))
    {
      try
      {
        primerak->setGlobal(simbol);
      }
      catch (Error* e) { throw yy::parser::syntax_error(drv.location,e->mess);}
    }
  };

global_directive:
  GLOBAL list_of_only_symbols {
    SymbolTable* primerak = SymbolTable::getOnlySymbolTable();
    for (string& simbol : (*$2))
    {
      primerak->setGlobal(simbol);
    }
  };

list_of_only_symbols:
  SYMBOL {$$ = new std::vector<std::string>(); $$->push_back($1);}
  | list_of_only_symbols "," SYMBOL {$1->push_back($3); $$=$1;};

list_of_symbols:
    SYMBOL {$$ = new std::vector<std::string>(); $$->push_back($1);}
  | literal {$$ = new std::vector<std::string>(); $$->push_back(to_string($1));}
  | list_of_symbols "," SYMBOL {$1->push_back($3); $$=$1;}
  | list_of_symbols "," literal {$1->push_back(to_string($3)); $$=$1;};

instruction:
    EMPTYINS { $$=new Instruction($1); drv.add_to_instructions($$); }
    | ONEINS operand_reg {$$ = new Instruction($1,$2); drv.add_to_instructions($$);}
    | TWOINS operand_reg "," operand_reg {$$ = new Instruction($1,$2,$4); drv.add_to_instructions($$);}
    | NOTINS operand_reg {$$ = new Instruction($1,$2,new DirOpReg("r0")); drv.add_to_instructions($$);}
    | JMPINS operand_jump {$$ = new Instruction($1,$2); drv.add_to_instructions($$);}
    | LDRSTRINS operand_reg "," operand_arithm {$$ = new Instruction($1,$2,$4); drv.add_to_instructions($$);}
    | LDRSTRINS operand_reg "," operand_reg {$$ = new Instruction($1,$2,$4); drv.add_to_instructions($$);}
    | WORD list_of_symbols {
      for (string& sym : (*$2))
      {
        if (sym[0]>='0' && sym[0]<='9')
        {
          Operand* op = new DirOpLit(stoi(sym));
          $$ = new Instruction($1,op); drv.add_to_instructions($$);
        }
        else
        {
          Operand* op = new DirOpSym(sym);
          $$ = new Instruction($1,op); drv.add_to_instructions($$);
        }
      }
    }
    | SKIP literal
    {
      Operand* op = new DirOpLit($2);
      $$ = new Instruction($1,op); drv.add_to_instructions($$);
    }

operand_reg:
    REG {$$ = new DirOpReg($1);};

operand_arithm:
    "$" literal {$$ = new DirOpLit($2);}
  | "$" SYMBOL {$$ = new DirOpSym($2);}
  | literal {$$ = new MemOpLit($1);}
  | SYMBOL {$$ = new MemOpSym($1);}
  | "%" SYMBOL {$$ = new PCRelOpSym($2);}
  | "[" REG "]" {$$ = new MemOpReg($2);}
  | "[" REG "+" literal "]" {$$ = new MemPomOpRegLit($2,$4);}
  | "[" REG "+" SYMBOL "]" {$$ = new MemPomOpRegSym($2,$4);};

operand_jump:
    literal {$$ = new DirOpLit($1);}
  | SYMBOL {$$ = new DirOpSym($1);}
  | "%" SYMBOL {$$ = new PCRelOpSymReg($2);}
  | "*" SYMBOL {$$ = new MemOpSym($2);}
  | "*" literal {$$ = new MemOpLit($2);}
  | "*" REG {$$ = new DirOpReg($2);}
  | "*" "[" REG "]" { $$ = new MemOpReg($3);}
  | "*" "[" REG "+" literal "]" {$$ = new MemPomOpRegLit($3,$5);}
  | "*" "[" REG "+" SYMBOL "]" {$$ = new MemPomOpRegSym($3,$5);};

literal:
    DECIMAL {$$ = $1;}
  | HEX {$$ = $1;}
  | "-" DECIMAL {$$ = -$2;}
  | "-" HEX {$$ = -$2;};

%%
void yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}