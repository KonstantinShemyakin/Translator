#ifndef TRN_INHELP_H
#define TRN_INHELP_H

#include <chrono>

class TInHelp {
public:
   enum T_Mode { None, Parse, Syntax, Rules, Table, YACC, Grammar, Translate };
public:
   TInHelp(int m);
   ~TInHelp();
   int  input(int argc, const char* argv[]);
public:
   void option_mode() const;
   void table_mode() const;
   void parse_mode() const;
   void make_mode() const;
   void grammar_mode() const;
   void build_mode() const;
public:
   void parse_help() const;
   void rules_help() const;
   void syntax_help() const;
   void yacc_help() const;
   void grammar_help() const;
   void table_help() const;
   void translator_help() const;
   void help() const;
public:
   int count;
   int type;
   int option, mode;
   const char* file;
   const char* table;
public:
   std::chrono::time_point<std::chrono::system_clock> start, end;
protected:
   int program;
};

#endif