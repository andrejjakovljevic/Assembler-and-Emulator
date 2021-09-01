#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class SymbolTable
{

public:
    static SymbolTable* onlySymbolTable; 

    struct Entry
    {
        int type; // 1- local; 2-global; 3-section
        string section; // abs - absolute
        int value; 
        bool is_undefined;

        Entry() = default;  

        Entry(int type, string section, int value, bool is_undefined)
        {
            this->type=type;
            this->section=section;
            this->value=value;
            this->is_undefined=is_undefined;
        }

        void print(ofstream& mf)
        {
            const char separator    = ' ';
            const int numWidth      = 10;
            mf << left << setw(numWidth) << setfill(separator) << ((type==1)?('L'):((type==2)?('G'):('S')));
            mf << left << setw(numWidth) << setfill(separator) << section;
            mf << left << setw(numWidth) << setfill(separator) << value;
            mf << left << setw(numWidth) << setfill(separator) << (is_undefined?"NE":"DA");
            mf << endl; 
        }

        bool is_global()
        {
            return type==2;
        }

    };

    map<string,Entry> table;


    void addEntry(string symbol, string section, int value);
    void addLinkerEntry(string symbol, int type, string section, int value, bool is_undefined);
    void addSection(string section);
    void setGlobal(string symbol);
    int get_val(string symbol); //only if exists
    bool undefined(string symbol); //only if exists
    void addExtern(string symbol);
    bool exists(string symbol); 
    void print(ofstream& mf);
    void printBinary(ofstream& mf);

    static SymbolTable* getOnlySymbolTable();

};



#endif