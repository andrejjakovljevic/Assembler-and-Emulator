// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "parser.h"


// Unqualified %code blocks.
#line 27 "src/parser.y"

#include "driver.h"
#include <iostream>

#line 50 "src/parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 141 "src/parser.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser (driver& drv_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      drv (drv_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 44: // instruction
        value.YY_MOVE_OR_COPY< Instruction* > (YY_MOVE (that.value));
        break;

      case 45: // operand_reg
      case 46: // operand_arithm
      case 47: // operand_jump
        value.YY_MOVE_OR_COPY< Operand* > (YY_MOVE (that.value));
        break;

      case 15: // DECIMAL
      case 16: // HEX
      case 48: // literal
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 17: // WORD
      case 18: // SKIP
      case 19: // SYMBOL
      case 20: // REG
      case 21: // EMPTYINS
      case 22: // JMPINS
      case 23: // ONEINS
      case 24: // TWOINS
      case 25: // LDRSTRINS
      case 26: // NOTINS
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case 42: // list_of_only_symbols
      case 43: // list_of_symbols
        value.YY_MOVE_OR_COPY< std::vector<std::string>* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 44: // instruction
        value.move< Instruction* > (YY_MOVE (that.value));
        break;

      case 45: // operand_reg
      case 46: // operand_arithm
      case 47: // operand_jump
        value.move< Operand* > (YY_MOVE (that.value));
        break;

      case 15: // DECIMAL
      case 16: // HEX
      case 48: // literal
        value.move< int > (YY_MOVE (that.value));
        break;

      case 17: // WORD
      case 18: // SKIP
      case 19: // SYMBOL
      case 20: // REG
      case 21: // EMPTYINS
      case 22: // JMPINS
      case 23: // ONEINS
      case 24: // TWOINS
      case 25: // LDRSTRINS
      case 26: // NOTINS
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case 42: // list_of_only_symbols
      case 43: // list_of_symbols
        value.move< std::vector<std::string>* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 44: // instruction
        value.copy< Instruction* > (that.value);
        break;

      case 45: // operand_reg
      case 46: // operand_arithm
      case 47: // operand_jump
        value.copy< Operand* > (that.value);
        break;

      case 15: // DECIMAL
      case 16: // HEX
      case 48: // literal
        value.copy< int > (that.value);
        break;

      case 17: // WORD
      case 18: // SKIP
      case 19: // SYMBOL
      case 20: // REG
      case 21: // EMPTYINS
      case 22: // JMPINS
      case 23: // ONEINS
      case 24: // TWOINS
      case 25: // LDRSTRINS
      case 26: // NOTINS
        value.copy< std::string > (that.value);
        break;

      case 42: // list_of_only_symbols
      case 43: // list_of_symbols
        value.copy< std::vector<std::string>* > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 44: // instruction
        value.move< Instruction* > (that.value);
        break;

      case 45: // operand_reg
      case 46: // operand_arithm
      case 47: // operand_jump
        value.move< Operand* > (that.value);
        break;

      case 15: // DECIMAL
      case 16: // HEX
      case 48: // literal
        value.move< int > (that.value);
        break;

      case 17: // WORD
      case 18: // SKIP
      case 19: // SYMBOL
      case 20: // REG
      case 21: // EMPTYINS
      case 22: // JMPINS
      case 23: // ONEINS
      case 24: // TWOINS
      case 25: // LDRSTRINS
      case 26: // NOTINS
        value.move< std::string > (that.value);
        break;

      case 42: // list_of_only_symbols
      case 43: // list_of_symbols
        value.move< std::vector<std::string>* > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
      case 15: // DECIMAL
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < int > (); }
#line 473 "src/parser.cpp"
        break;

      case 16: // HEX
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < int > (); }
#line 479 "src/parser.cpp"
        break;

      case 17: // WORD
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 485 "src/parser.cpp"
        break;

      case 18: // SKIP
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 491 "src/parser.cpp"
        break;

      case 19: // SYMBOL
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 497 "src/parser.cpp"
        break;

      case 20: // REG
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 503 "src/parser.cpp"
        break;

      case 21: // EMPTYINS
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 509 "src/parser.cpp"
        break;

      case 22: // JMPINS
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 515 "src/parser.cpp"
        break;

      case 23: // ONEINS
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 521 "src/parser.cpp"
        break;

      case 24: // TWOINS
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 527 "src/parser.cpp"
        break;

      case 25: // LDRSTRINS
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 533 "src/parser.cpp"
        break;

      case 26: // NOTINS
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 539 "src/parser.cpp"
        break;

      case 42: // list_of_only_symbols
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < std::vector<std::string>* > (); }
#line 545 "src/parser.cpp"
        break;

      case 43: // list_of_symbols
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < std::vector<std::string>* > (); }
#line 551 "src/parser.cpp"
        break;

      case 44: // instruction
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < Instruction* > (); }
#line 557 "src/parser.cpp"
        break;

      case 45: // operand_reg
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < Operand* > (); }
#line 563 "src/parser.cpp"
        break;

      case 46: // operand_arithm
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < Operand* > (); }
#line 569 "src/parser.cpp"
        break;

      case 47: // operand_jump
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < Operand* > (); }
#line 575 "src/parser.cpp"
        break;

      case 48: // literal
#line 68 "src/parser.y"
                 { yyoutput << yysym.value.template as < int > (); }
#line 581 "src/parser.cpp"
        break;

      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (drv));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 44: // instruction
        yylhs.value.emplace< Instruction* > ();
        break;

      case 45: // operand_reg
      case 46: // operand_arithm
      case 47: // operand_jump
        yylhs.value.emplace< Operand* > ();
        break;

      case 15: // DECIMAL
      case 16: // HEX
      case 48: // literal
        yylhs.value.emplace< int > ();
        break;

      case 17: // WORD
      case 18: // SKIP
      case 19: // SYMBOL
      case 20: // REG
      case 21: // EMPTYINS
      case 22: // JMPINS
      case 23: // ONEINS
      case 24: // TWOINS
      case 25: // LDRSTRINS
      case 26: // NOTINS
        yylhs.value.emplace< std::string > ();
        break;

      case 42: // list_of_only_symbols
      case 43: // list_of_symbols
        yylhs.value.emplace< std::vector<std::string>* > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 74 "src/parser.y"
          {}
#line 856 "src/parser.cpp"
    break;

  case 3:
#line 77 "src/parser.y"
                              {}
#line 862 "src/parser.cpp"
    break;

  case 4:
#line 80 "src/parser.y"
         {}
#line 868 "src/parser.cpp"
    break;

  case 5:
#line 81 "src/parser.y"
                     {}
#line 874 "src/parser.cpp"
    break;

  case 6:
#line 84 "src/parser.y"
         {}
#line 880 "src/parser.cpp"
    break;

  case 7:
#line 85 "src/parser.y"
                         {}
#line 886 "src/parser.cpp"
    break;

  case 8:
#line 86 "src/parser.y"
                            {}
#line 892 "src/parser.cpp"
    break;

  case 9:
#line 87 "src/parser.y"
                            {}
#line 898 "src/parser.cpp"
    break;

  case 10:
#line 90 "src/parser.y"
                                {}
#line 904 "src/parser.cpp"
    break;

  case 11:
#line 93 "src/parser.y"
         {}
#line 910 "src/parser.cpp"
    break;

  case 12:
#line 94 "src/parser.y"
                      {}
#line 916 "src/parser.cpp"
    break;

  case 13:
#line 97 "src/parser.y"
              {}
#line 922 "src/parser.cpp"
    break;

  case 14:
#line 98 "src/parser.y"
          {}
#line 928 "src/parser.cpp"
    break;

  case 15:
#line 99 "src/parser.y"
                     {}
#line 934 "src/parser.cpp"
    break;

  case 16:
#line 100 "src/parser.y"
                     {}
#line 940 "src/parser.cpp"
    break;

  case 17:
#line 101 "src/parser.y"
                  {}
#line 946 "src/parser.cpp"
    break;

  case 18:
#line 105 "src/parser.y"
  {
    drv.add_section(yystack_[0].value.as < std::string > (),drv.lc);
    SymbolTable* primerak = SymbolTable::getOnlySymbolTable();
    primerak->addSection(yystack_[0].value.as < std::string > ());
  }
#line 956 "src/parser.cpp"
    break;

  case 19:
#line 112 "src/parser.y"
      {drv.fixLast(); return 0;}
#line 962 "src/parser.cpp"
    break;

  case 20:
#line 116 "src/parser.y"
  {
    SymbolTable* primerak = SymbolTable::getOnlySymbolTable();
    if (primerak->exists(yystack_[1].value.as < std::string > ()))
    {
      if (!primerak->undefined(yystack_[1].value.as < std::string > ())) throw yy::parser::syntax_error(drv.location,"Already defined");
    }
    primerak->addEntry(yystack_[1].value.as < std::string > (), drv.section_infos[drv.section_infos.size()-1]->section_name, drv.lc);
  }
#line 975 "src/parser.cpp"
    break;

  case 21:
#line 127 "src/parser.y"
  {
    SymbolTable* primerak = SymbolTable::getOnlySymbolTable();
    if (primerak->exists(yystack_[2].value.as < std::string > ()))
    {
      if (!primerak->undefined(yystack_[2].value.as < std::string > ())) throw yy::parser::syntax_error(drv.location,"Already defined");
    }
    primerak->addEntry(yystack_[2].value.as < std::string > (), "abs", yystack_[0].value.as < int > ());
  }
#line 988 "src/parser.cpp"
    break;

  case 22:
#line 138 "src/parser.y"
  {
    SymbolTable* primerak = SymbolTable::getOnlySymbolTable();
    for (string& simbol : (*yystack_[0].value.as < std::vector<std::string>* > ()))
    {
      try
      {
        primerak->setGlobal(simbol);
      }
      catch (Error* e) { throw yy::parser::syntax_error(drv.location,e->mess);}
    }
  }
#line 1004 "src/parser.cpp"
    break;

  case 23:
#line 151 "src/parser.y"
                              {
    SymbolTable* primerak = SymbolTable::getOnlySymbolTable();
    for (string& simbol : (*yystack_[0].value.as < std::vector<std::string>* > ()))
    {
      primerak->setGlobal(simbol);
    }
  }
#line 1016 "src/parser.cpp"
    break;

  case 24:
#line 160 "src/parser.y"
         {yylhs.value.as < std::vector<std::string>* > () = new std::vector<std::string>(); yylhs.value.as < std::vector<std::string>* > ()->push_back(yystack_[0].value.as < std::string > ());}
#line 1022 "src/parser.cpp"
    break;

  case 25:
#line 161 "src/parser.y"
                                    {yystack_[2].value.as < std::vector<std::string>* > ()->push_back(yystack_[0].value.as < std::string > ()); yylhs.value.as < std::vector<std::string>* > ()=yystack_[2].value.as < std::vector<std::string>* > ();}
#line 1028 "src/parser.cpp"
    break;

  case 26:
#line 164 "src/parser.y"
           {yylhs.value.as < std::vector<std::string>* > () = new std::vector<std::string>(); yylhs.value.as < std::vector<std::string>* > ()->push_back(yystack_[0].value.as < std::string > ());}
#line 1034 "src/parser.cpp"
    break;

  case 27:
#line 165 "src/parser.y"
            {yylhs.value.as < std::vector<std::string>* > () = new std::vector<std::string>(); yylhs.value.as < std::vector<std::string>* > ()->push_back(to_string(yystack_[0].value.as < int > ()));}
#line 1040 "src/parser.cpp"
    break;

  case 28:
#line 166 "src/parser.y"
                               {yystack_[2].value.as < std::vector<std::string>* > ()->push_back(yystack_[0].value.as < std::string > ()); yylhs.value.as < std::vector<std::string>* > ()=yystack_[2].value.as < std::vector<std::string>* > ();}
#line 1046 "src/parser.cpp"
    break;

  case 29:
#line 167 "src/parser.y"
                                {yystack_[2].value.as < std::vector<std::string>* > ()->push_back(to_string(yystack_[0].value.as < int > ())); yylhs.value.as < std::vector<std::string>* > ()=yystack_[2].value.as < std::vector<std::string>* > ();}
#line 1052 "src/parser.cpp"
    break;

  case 30:
#line 170 "src/parser.y"
             { yylhs.value.as < Instruction* > ()=new Instruction(yystack_[0].value.as < std::string > ()); drv.add_to_instructions(yylhs.value.as < Instruction* > ()); }
#line 1058 "src/parser.cpp"
    break;

  case 31:
#line 171 "src/parser.y"
                         {yylhs.value.as < Instruction* > () = new Instruction(yystack_[1].value.as < std::string > (),yystack_[0].value.as < Operand* > ()); drv.add_to_instructions(yylhs.value.as < Instruction* > ());}
#line 1064 "src/parser.cpp"
    break;

  case 32:
#line 172 "src/parser.y"
                                         {yylhs.value.as < Instruction* > () = new Instruction(yystack_[3].value.as < std::string > (),yystack_[2].value.as < Operand* > (),yystack_[0].value.as < Operand* > ()); drv.add_to_instructions(yylhs.value.as < Instruction* > ());}
#line 1070 "src/parser.cpp"
    break;

  case 33:
#line 173 "src/parser.y"
                         {yylhs.value.as < Instruction* > () = new Instruction(yystack_[1].value.as < std::string > (),yystack_[0].value.as < Operand* > (),new DirOpReg("r0")); drv.add_to_instructions(yylhs.value.as < Instruction* > ());}
#line 1076 "src/parser.cpp"
    break;

  case 34:
#line 174 "src/parser.y"
                          {yylhs.value.as < Instruction* > () = new Instruction(yystack_[1].value.as < std::string > (),yystack_[0].value.as < Operand* > ()); drv.add_to_instructions(yylhs.value.as < Instruction* > ());}
#line 1082 "src/parser.cpp"
    break;

  case 35:
#line 175 "src/parser.y"
                                               {yylhs.value.as < Instruction* > () = new Instruction(yystack_[3].value.as < std::string > (),yystack_[2].value.as < Operand* > (),yystack_[0].value.as < Operand* > ()); drv.add_to_instructions(yylhs.value.as < Instruction* > ());}
#line 1088 "src/parser.cpp"
    break;

  case 36:
#line 176 "src/parser.y"
                                            {yylhs.value.as < Instruction* > () = new Instruction(yystack_[3].value.as < std::string > (),yystack_[2].value.as < Operand* > (),yystack_[0].value.as < Operand* > ()); drv.add_to_instructions(yylhs.value.as < Instruction* > ());}
#line 1094 "src/parser.cpp"
    break;

  case 37:
#line 177 "src/parser.y"
                           {
      for (string& sym : (*yystack_[0].value.as < std::vector<std::string>* > ()))
      {
        if (sym[0]>='0' && sym[0]<='9')
        {
          Operand* op = new DirOpLit(stoi(sym));
          yylhs.value.as < Instruction* > () = new Instruction(yystack_[1].value.as < std::string > (),op); drv.add_to_instructions(yylhs.value.as < Instruction* > ());
        }
        else
        {
          Operand* op = new DirOpSym(sym);
          yylhs.value.as < Instruction* > () = new Instruction(yystack_[1].value.as < std::string > (),op); drv.add_to_instructions(yylhs.value.as < Instruction* > ());
        }
      }
    }
#line 1114 "src/parser.cpp"
    break;

  case 38:
#line 193 "src/parser.y"
    {
      Operand* op = new DirOpLit(yystack_[0].value.as < int > ());
      yylhs.value.as < Instruction* > () = new Instruction(yystack_[1].value.as < std::string > (),op); drv.add_to_instructions(yylhs.value.as < Instruction* > ());
    }
#line 1123 "src/parser.cpp"
    break;

  case 39:
#line 199 "src/parser.y"
        {yylhs.value.as < Operand* > () = new DirOpReg(yystack_[0].value.as < std::string > ());}
#line 1129 "src/parser.cpp"
    break;

  case 40:
#line 202 "src/parser.y"
                {yylhs.value.as < Operand* > () = new DirOpLit(yystack_[0].value.as < int > ());}
#line 1135 "src/parser.cpp"
    break;

  case 41:
#line 203 "src/parser.y"
               {yylhs.value.as < Operand* > () = new DirOpSym(yystack_[0].value.as < std::string > ());}
#line 1141 "src/parser.cpp"
    break;

  case 42:
#line 204 "src/parser.y"
            {yylhs.value.as < Operand* > () = new MemOpLit(yystack_[0].value.as < int > ());}
#line 1147 "src/parser.cpp"
    break;

  case 43:
#line 205 "src/parser.y"
           {yylhs.value.as < Operand* > () = new MemOpSym(yystack_[0].value.as < std::string > ());}
#line 1153 "src/parser.cpp"
    break;

  case 44:
#line 206 "src/parser.y"
               {yylhs.value.as < Operand* > () = new PCRelOpSym(yystack_[0].value.as < std::string > ());}
#line 1159 "src/parser.cpp"
    break;

  case 45:
#line 207 "src/parser.y"
                {yylhs.value.as < Operand* > () = new MemOpReg(yystack_[1].value.as < std::string > ());}
#line 1165 "src/parser.cpp"
    break;

  case 46:
#line 208 "src/parser.y"
                            {yylhs.value.as < Operand* > () = new MemPomOpRegLit(yystack_[3].value.as < std::string > (),yystack_[1].value.as < int > ());}
#line 1171 "src/parser.cpp"
    break;

  case 47:
#line 209 "src/parser.y"
                           {yylhs.value.as < Operand* > () = new MemPomOpRegSym(yystack_[3].value.as < std::string > (),yystack_[1].value.as < std::string > ());}
#line 1177 "src/parser.cpp"
    break;

  case 48:
#line 212 "src/parser.y"
            {yylhs.value.as < Operand* > () = new DirOpLit(yystack_[0].value.as < int > ());}
#line 1183 "src/parser.cpp"
    break;

  case 49:
#line 213 "src/parser.y"
           {yylhs.value.as < Operand* > () = new DirOpSym(yystack_[0].value.as < std::string > ());}
#line 1189 "src/parser.cpp"
    break;

  case 50:
#line 214 "src/parser.y"
               {yylhs.value.as < Operand* > () = new PCRelOpSymReg(yystack_[0].value.as < std::string > ());}
#line 1195 "src/parser.cpp"
    break;

  case 51:
#line 215 "src/parser.y"
               {yylhs.value.as < Operand* > () = new MemOpSym(yystack_[0].value.as < std::string > ());}
#line 1201 "src/parser.cpp"
    break;

  case 52:
#line 216 "src/parser.y"
                {yylhs.value.as < Operand* > () = new MemOpLit(yystack_[0].value.as < int > ());}
#line 1207 "src/parser.cpp"
    break;

  case 53:
#line 217 "src/parser.y"
            {yylhs.value.as < Operand* > () = new DirOpReg(yystack_[0].value.as < std::string > ());}
#line 1213 "src/parser.cpp"
    break;

  case 54:
#line 218 "src/parser.y"
                    { yylhs.value.as < Operand* > () = new MemOpReg(yystack_[1].value.as < std::string > ());}
#line 1219 "src/parser.cpp"
    break;

  case 55:
#line 219 "src/parser.y"
                                {yylhs.value.as < Operand* > () = new MemPomOpRegLit(yystack_[3].value.as < std::string > (),yystack_[1].value.as < int > ());}
#line 1225 "src/parser.cpp"
    break;

  case 56:
#line 220 "src/parser.y"
                               {yylhs.value.as < Operand* > () = new MemPomOpRegSym(yystack_[3].value.as < std::string > (),yystack_[1].value.as < std::string > ());}
#line 1231 "src/parser.cpp"
    break;

  case 57:
#line 223 "src/parser.y"
            {yylhs.value.as < int > () = yystack_[0].value.as < int > ();}
#line 1237 "src/parser.cpp"
    break;

  case 58:
#line 224 "src/parser.y"
        {yylhs.value.as < int > () = yystack_[0].value.as < int > ();}
#line 1243 "src/parser.cpp"
    break;

  case 59:
#line 225 "src/parser.y"
                {yylhs.value.as < int > () = -yystack_[0].value.as < int > ();}
#line 1249 "src/parser.cpp"
    break;

  case 60:
#line 226 "src/parser.y"
            {yylhs.value.as < int > () = -yystack_[0].value.as < int > ();}
#line 1255 "src/parser.cpp"
    break;


#line 1259 "src/parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -42;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
     -42,    21,   -42,    -4,   -42,     3,     8,    15,     6,   -42,
     -42,   -42,   -42,    32,   -42,   -42,   -42,    16,    33,   -42,
      37,   -42,    17,   -42,   -42,   -42,    39,   -42,   -42,    57,
      -2,   -42,    45,   -42,   -42,   -42,   -42,     8,    -2,    44,
     -42,     1,    68,    68,    68,    68,   -42,   -42,   -42,   -42,
     -42,   -42,    33,   -42,   -42,    34,    46,   -42,   -42,   -42,
     -42,   -42,    69,    81,   -42,    72,   -42,   -42,   -42,   -42,
      68,    28,    12,   -42,    74,    59,    76,   -42,   -42,   -42,
     -42,    64,   -42,    84,   -42,   -42,   -42,    90,    91,    66,
     -42,   -42,   -42,    92,    93,   -42,   -42
  };

  const signed char
  parser::yydefact_[] =
  {
       6,     0,     2,     4,     1,     0,     0,     0,     0,     7,
       9,     8,    24,    23,    57,    58,    26,     0,    22,    27,
       0,    19,     0,     5,    11,     3,     0,    59,    60,     0,
       0,    18,    10,    25,    28,    29,    21,     0,     0,     0,
      30,     0,     0,     0,     0,     0,    12,    14,    17,    16,
      15,    13,    37,    38,    20,     0,     0,    49,    34,    48,
      39,    31,     0,     0,    33,     0,    51,    53,    52,    50,
       0,     0,     0,    32,     0,     0,     0,    43,    36,    35,
      42,     0,    54,     0,    41,    40,    44,     0,     0,     0,
      45,    56,    55,     0,     0,    47,    46
  };

  const signed char
  parser::yypgoto_[] =
  {
     -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,
     -42,    70,    71,    73,   -42,    63,   -42,   -41,   -42,   -42,
     -29
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     1,     2,     8,     3,    23,    32,    46,    24,    25,
      47,     9,    10,    11,    13,    18,    51,    61,    79,    58,
      19
  };

  const signed char
  parser::yytable_[] =
  {
      35,    36,    62,    63,    64,    55,    21,     5,     6,    53,
       7,    56,    59,    14,    15,    81,    14,    15,    82,    22,
      57,     4,    12,    14,    15,    17,    68,    16,    17,    73,
      78,    27,    28,    74,    20,    17,    31,    75,    76,    65,
      26,    29,    80,    14,    15,    30,    85,    77,    60,    14,
      15,    54,    88,    66,    67,    17,     5,     6,    33,     7,
      94,    17,    37,    38,    39,    69,    40,    41,    42,    43,
      44,    45,    14,    15,    14,    15,    34,    70,    84,    14,
      15,    14,    15,    87,    17,    93,    17,    89,    60,    71,
      90,    17,    72,    17,    83,    86,    91,    92,    95,    96,
      52,     0,    48,    49,     0,    50
  };

  const signed char
  parser::yycheck_[] =
  {
      29,    30,    43,    44,    45,     4,     0,    11,    12,    38,
      14,    10,    41,    15,    16,     3,    15,    16,     6,    13,
      19,     0,    19,    15,    16,    27,    55,    19,    27,    70,
      71,    15,    16,     5,    19,    27,    19,     9,    10,     5,
       8,     8,    71,    15,    16,     8,    75,    19,    20,    15,
      16,     7,    81,    19,    20,    27,    11,    12,    19,    14,
      89,    27,    17,    18,    19,    19,    21,    22,    23,    24,
      25,    26,    15,    16,    15,    16,    19,     8,    19,    15,
      16,    15,    16,    19,    27,    19,    27,     3,    20,     8,
       6,    27,    20,    27,    20,    19,     6,     6,     6,     6,
      37,    -1,    32,    32,    -1,    32
  };

  const signed char
  parser::yystos_[] =
  {
       0,    29,    30,    32,     0,    11,    12,    14,    31,    39,
      40,    41,    19,    42,    15,    16,    19,    27,    43,    48,
      19,     0,    13,    33,    36,    37,     8,    15,    16,     8,
       8,    19,    34,    19,    19,    48,    48,    17,    18,    19,
      21,    22,    23,    24,    25,    26,    35,    38,    39,    40,
      41,    44,    43,    48,     7,     4,    10,    19,    47,    48,
      20,    45,    45,    45,    45,     5,    19,    20,    48,    19,
       8,     8,    20,    45,     5,     9,    10,    19,    45,    46,
      48,     3,     6,    20,    19,    48,    19,    19,    48,     3,
       6,     6,     6,    19,    48,     6,     6
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    28,    29,    30,    31,    31,    32,    32,    32,    32,
      33,    34,    34,    35,    35,    35,    35,    35,    36,    37,
      38,    39,    40,    41,    42,    42,    43,    43,    43,    43,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    45,
      46,    46,    46,    46,    46,    46,    46,    46,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    48,    48,    48,
      48
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     3,     0,     2,     0,     2,     2,     2,
       2,     0,     2,     1,     1,     1,     1,     1,     2,     1,
       2,     4,     2,     2,     1,     3,     1,     1,     3,     3,
       1,     2,     4,     2,     2,     4,     4,     2,     2,     1,
       2,     2,     1,     1,     2,     3,     5,     5,     1,     1,
       2,     2,     2,     2,     4,     6,     6,     1,     1,     2,
       2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"+\"", "\"*\"", "\"[\"",
  "\"]\"", "\":\"", "\",\"", "\"$\"", "\"%\"", "GLOBAL", "EXTERN",
  "SECTION", "EQU", "DECIMAL", "HEX", "WORD", "SKIP", "SYMBOL", "REG",
  "EMPTYINS", "JMPINS", "ONEINS", "TWOINS", "LDRSTRINS", "NOTINS", "\"-\"",
  "$accept", "program_start", "program", "sections", "header", "section",
  "instructions", "line", "section_begining", "end_program", "label",
  "equ_directive", "extern_directive", "global_directive",
  "list_of_only_symbols", "list_of_symbols", "instruction", "operand_reg",
  "operand_arithm", "operand_jump", "literal", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,    74,    74,    77,    80,    81,    84,    85,    86,    87,
      90,    93,    94,    97,    98,    99,   100,   101,   104,   112,
     115,   126,   137,   151,   160,   161,   164,   165,   166,   167,
     170,   171,   172,   173,   174,   175,   176,   177,   192,   199,
     202,   203,   204,   205,   206,   207,   208,   209,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   223,   224,   225,
     226
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1713 "src/parser.cpp"

#line 228 "src/parser.y"

void yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
