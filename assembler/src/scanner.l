%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include "driver.h"
# include "parser.h"

// Pacify warnings in yy_init_buffer (observed with Flex 2.6.4)
// and GCC 7.3.0.
#if defined __GNUC__ && 7 <= __GNUC__
# pragma GCC diagnostic ignored "-Wnull-dereference"
#endif
%}

%option noyywrap nounput batch debug noinput

%{
  yy::parser::symbol_type make_DECIMAL (const std::string &s, const yy::parser::location_type& loc);
  yy::parser::symbol_type make_HEX (const std::string &s, const yy::parser::location_type& loc);
%}

decimal (([1-9][0-9]*)|0)
blank [ \t\r]
symbol [a-zA-Z_][a-zA-Z_0-9]*
hex 0[xX][0-9a-fA-F]+
komentar #.*

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}
%%
%{
  // A handy shortcut to the location held by the driver.
  yy::location& loc = drv.location;
  // Code run each time yylex is called.
  loc.step ();
%}
{blank}+   loc.step ();
[\n]+      loc.lines (yyleng); loc.step ();

"+"         return yy::parser::make_PLUS    (loc);
"*"         return yy::parser::make_STAR    (loc);
"["         return yy::parser::make_LPAREN  (loc);
"]"         return yy::parser::make_RPAREN  (loc);
":"         return yy::parser::make_COLON   (loc);
","         return yy::parser::make_COMMA   (loc);
"$"         return yy::parser::make_DOLAR   (loc);
"%"         return yy::parser::make_PERCENT (loc);
".global"   return yy::parser::make_GLOBAL  (loc);
".extern"   return yy::parser::make_EXTERN  (loc);
".section"  return yy::parser::make_SECTION (loc);
".end"      return yy::parser::make_END     (loc);
".skip"     return yy::parser::make_SKIP    (yytext,loc);
".equ"      return yy::parser::make_EQU     (loc);
".word"     return yy::parser::make_WORD    (yytext,loc);
{komentar}  {};
{decimal}   return make_DECIMAL (yytext,loc);
{hex}       return make_HEX (yytext,loc);
(halt|iret|ret) return yy::parser::make_EMPTYINS (yytext,loc);
(call|jmp|jeq|jne|jgt) return yy::parser::make_JMPINS (yytext,loc);
(int|push|pop) return yy::parser::make_ONEINS (yytext,loc);
(ldr|str) return yy::parser::make_LDRSTRINS (yytext, loc);
(xchg|add|sub|mul|div|cmp|and|or|xor|test|shl|shr) return yy::parser::make_TWOINS (yytext,loc);
(not) return yy::parser::make_NOTINS (yytext,loc);
(r[0-7]|sp|psw|pc) return yy::parser::make_REG (yytext,loc);
{symbol} return yy::parser::make_SYMBOL (yytext,loc);


<<EOF>> return yy::parser::make_END(loc);

%%

yy::parser::symbol_type make_DECIMAL(const std::string &s, const yy::parser::location_type& loc)
{
  return yy::parser::make_DECIMAL(std::stoi(s,nullptr,10),loc);
}

yy::parser::symbol_type make_HEX (const std::string &s, const yy::parser::location_type& loc)
{
  return yy::parser::make_HEX(std::stoi(s,nullptr,16),loc);
}

void driver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (file.empty () || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      std::cerr << "cannot open " << file << ": " << strerror(errno) << '\n';
      exit (EXIT_FAILURE);
    }
}

void driver::scan_end ()
{
  fclose (yyin);
}