#include "symboltable.h"
#include "error.h"
#include <iomanip>
#include <fstream>
using namespace std;

SymbolTable* SymbolTable::onlySymbolTable=nullptr;

bool SymbolTable::exists(string symbol)
{
    if (table.find(symbol)==table.end()) return false;
    else return true;
}

void SymbolTable::addEntry(string symbol, string section, int value)
{
    int tip = 1;
    if (exists(symbol)) tip=table[symbol].type;
    Entry e(tip,section,value,false);
    table[symbol]=e;
}

void SymbolTable::addLinkerEntry(string symbol, int type, string section, int value, bool is_undefined)
{
    Entry e(type,section,value,is_undefined);
    table[symbol]=e;
}


int SymbolTable::get_val(string symbol)
{
    return table[symbol].value;
}

void SymbolTable::setGlobal(string symbol) 
{
    if (exists(symbol))
    {
        if (table[symbol].type==2)
        {
            throw new Error("Can't be global twice, symbol:"+symbol);
        }
    }
    else
    {
        addExtern(symbol);
    }
    table[symbol].type=2;
}

void SymbolTable::addSection(string section)
{
    if (!exists(section))
    {
        Entry e(3,section,0,false);
        table[section]=e;
    }
}

void SymbolTable::addExtern(string symbol)
{
    if (!exists(symbol))
    {
        Entry e(2,"",0,true);
        table[symbol]=e;
    }
}

void SymbolTable::print(ofstream& mf)
{
    const char separator    = ' ';
    const int numWidth      = 10;
    mf << "-------------------TABELA SIMBOLA----------------------" << endl;
    mf << left << setw(numWidth) << setfill(separator) << "Ime";
    mf << left << setw(numWidth) << setfill(separator) << "L/G/S";
    mf << left << setw(numWidth) << setfill(separator) << "Sekcija";
    mf << left << setw(numWidth) << setfill(separator) << "Vrednost";
    mf << left << setw(numWidth) << setfill(separator) << "Definisano";
    mf << endl;
    for (auto& entry : table)
    {
        if (entry.second.type==1) continue; // Ako neces lokalne, iskom ovo
        mf << left << setw(numWidth) << setfill(separator) << entry.first;
        entry.second.print(mf);
    }
}

SymbolTable* SymbolTable::getOnlySymbolTable()
{
    if (onlySymbolTable==nullptr)
    {
        onlySymbolTable = new SymbolTable();
        onlySymbolTable->addEntry("abs","abs",0);
        onlySymbolTable->setGlobal("abs");
    }
    return onlySymbolTable;
}

bool SymbolTable::undefined(string symbol)
{
    return table[symbol].is_undefined;
}