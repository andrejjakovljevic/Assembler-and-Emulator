#include "reallocation_table.h"
#include <iomanip>
#include <fstream>
using namespace std;

void ReallocationTable::addEntry(int addend, string symbol, int type, int offset)
{
    if (table.find(symbol)==table.end()) //nema nista
    {
        vector<Entry> v;
        table[symbol]=v;
        Entry e(addend, symbol, type, offset);
        table[symbol].push_back(e);
    }
    else
    {
        Entry e(addend, symbol, type, offset);
        table[symbol].push_back(e);
    }
}

bool ReallocationTable::exists(string symbol)
{
    return (table.find(symbol)!=table.end());
}

vector<ReallocationTable::Entry> ReallocationTable::returnEntry(string symbol)
{
    if (exists(symbol))
    {
        return table[symbol];
    }
    return vector<ReallocationTable::Entry>();
}

void ReallocationTable::print(ofstream& mf)
{
    mf << endl;
    mf << "relokacioni info:" << endl;
    const char separator    = ' ';
    const int numWidth      = 10;
    mf << left << setw(numWidth) << setfill(separator) << "Addend";
    mf << left << setw(numWidth) << setfill(separator) << "Simbol";
    mf << left << setw(numWidth) << setfill(separator) << "Tip";
    mf << left << setw(numWidth) << setfill(separator) << "Offset";
    mf << endl;
    for (auto& p : table)
    {
        for (auto& k : p.second)
        {
            k.print(mf);
        }
    }
}