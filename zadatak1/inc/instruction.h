#ifndef INSTRUCTION_HH
#define INSTRUCTION_HH
#include <cstdio>
#include <iostream>
#include <string>
#include "sectioninfo.h"
#include "symboltable.h"
using namespace std;

class Operand
{
public:
    string type;

    virtual bool needs_more() { return true; } // jel mu treba jos dva
    virtual string getSymbol()
    {
        return "";
    }

    virtual int getRegNumber()
    {
        return -1;
    }

    virtual char ABytes() = 0;

    virtual int getValue() { return -1; }

    Operand (string type)
    {
        this->type=type;
    }
};

class DirOpLit : public Operand
{
public:
    int value;

    DirOpLit (int k) : Operand("DirOpLit")
    {
        this->value=k;
    }
    virtual char ABytes()
    {
        return 0;
    }
    virtual int getValue() { return value; }
};

class DirOpSym : public Operand
{
public:
    string symbol;
    DirOpSym(string sym) : Operand("DirOpSym")
    {
        this->symbol=sym;
    }
    string getSymbol()
    {
        return symbol;
    }
    virtual char ABytes()
    {
        return 0;
    }
};

class MemOpSym : public Operand
{
public:
    string symbol;
    MemOpSym(string sym) : Operand("MemOpSym")
    {
        this->symbol=sym;
    }
    string getSymbol()
    {
        return symbol;
    }
    virtual char ABytes()
    {
        return 4;
    }
};

class MemOpLit : public Operand
{
 public:
    int value;

    MemOpLit (int k) : Operand("MemOpLit")
    {
        this->value=k;
    }

    virtual char ABytes()
    {
        return 4;
    }
    virtual int getValue() { return value; }

};

class PCRelOpSym : public Operand
{
public:
    string symbol;
    PCRelOpSym(string sym) : Operand("PCRelOpSym")
    {
        this->symbol=sym;
    }
    string getSymbol()
    {
        return symbol;
    }
    int getRegNumber()
    {
        return 7;
    }
    virtual char ABytes()
    {
        return 3;
    }
};

class PCRelOpSymReg : public Operand
{
public:
    string symbol;

    PCRelOpSymReg(string sym) : Operand("PCRelOpSymReg")
    {
        this->symbol=sym;
    }
    string getSymbol()
    {
        return symbol;
    }
    int getRegNumber()
    {
        return 7;
    }
    virtual char ABytes()
    {
        return 5;
    }

};

class DirOpReg : public Operand
{
public:
    string reg;
    bool needs_more() override
    {
        return false;
    }
    DirOpReg(string r) : Operand("DirOpReg")
    {
        this->reg=r;
    }
    int getRegNumber()
    {
        if (reg=="pc") return 7;
        if (reg=="sp") return 6;
        if (reg=="psw") return 8;
        return (int)(reg[1]-'0');
    }
    virtual char ABytes()
    {
        return 1;
    }
};

class MemOpReg : public Operand
{
public:
    string reg;
    bool needs_more() override
    {
        return false;
    }
    MemOpReg(string r) : Operand("MemOpReg")
    {
        this->reg=r;
    }
    int getRegNumber()
    {
        if (reg=="pc") return 7;
        if (reg=="sp") return 6;
        if (reg=="psw") return 8;
        return (int)(reg[1]-'0');
    }
    virtual char ABytes()
    {
        return 2;
    }
};

class MemPomOpRegLit : public Operand
{
public:
    string reg;
    int k;
    MemPomOpRegLit(string r, int k) : Operand("MemPomOpRegLit")
    {
        this->reg=r;
        this->k=k;
    }
    int getRegNumber()
    {
        if (reg=="pc") return 7;
        if (reg=="sp") return 6;
        if (reg=="psw") return 8;
        return (int)(reg[1]-'0');
    }

    virtual char ABytes()
    {
        return 3;
    }
    virtual int getValue() { return k; }
};

class MemPomOpRegSym : public Operand
{
public:
    string reg;
    string sym;
    MemPomOpRegSym(string reg, string sym) : Operand("MemPomOpRegSym")
    {
        this->reg=reg;
        this->sym=sym;
    }
    string getSymbol()
    {
        return sym;
    }
    int getRegNumber()
    {
        if (reg=="pc") return 7;
        if (reg=="sp") return 6;
        if (reg=="psw") return 8;
        return (int)(reg[1]-'0');
    }

    virtual char ABytes()
    {
        return 3;
    }
};

class Instruction
{
public:

    string instruction_name;
    Operand* op1;
    Operand* op2;

    Instruction(string instruction_name, Operand* op1, Operand* op2)
    {
        this->instruction_name=instruction_name;
        this->op1=op1;
        this->op2=op2;
    }

    Instruction(string instruction_name, Operand* op1)
    {
        this->instruction_name=instruction_name;
        this->op1=op1;
        this->op2=nullptr;
    }

    Instruction(string instruction_name)
    {
        this->instruction_name=instruction_name;
        this->op1=nullptr;
        this->op2=nullptr;
    }

    Instruction(Instruction* ins)
    {
        this->instruction_name=ins->instruction_name;
        this->op1=ins->op1;
        this->op2=ins->op2;
    }

    void print()
    {
        cout << instruction_name << " " << ((op1!=nullptr)? op1->type : "") << " " << ((op2!=nullptr)?op2->type:"") << " " << endl;
    }

    char getInsCode()
    {
        
        if (instruction_name=="halt")
        {
            return 0;
        }
        if (instruction_name=="int")
        {
            return 0x10;
        }
        if (instruction_name=="push")
        {
            return 0xb0;
        }
        if (instruction_name=="pop")
        {
            return 0xa0;
        }
        if (instruction_name=="iret")
        {
            return 0x20;
        }
        if (instruction_name=="call")
        {
            return 0x30;
        }
        if (instruction_name=="ret")
        {
            return 0x40;
        }
        if (instruction_name=="jmp")
        {
            return 0x50;
        }
        if  (instruction_name=="jeq")
        {
            return 0x51;
        }
        if (instruction_name=="jne")
        {
            return 0x52;
        }
        if (instruction_name=="jgt")
        {
            return 0x53;
        }
        if (instruction_name=="xchg")
        {
            return 0x60;
        }
        if (instruction_name=="add")
        {
            return 0x70;
        }
        if  (instruction_name=="sub")
        {
            return 0x71;
        }
        if (instruction_name=="mul")
        {
            return 0x72;
        }
        if  (instruction_name=="div")
        {
            return 0x73;
        }
        if  (instruction_name=="cmp")
        {
            return 0x74;
        }
        if (instruction_name=="not")
        {
            return 0x80;
        }
        if  (instruction_name=="and")
        {
            return 0x81;
        }
        if (instruction_name=="or")
        {
            return 0x82;
        }
        if (instruction_name=="xor")
        {
            return 0x83;
        }
        if  (instruction_name=="test")
        {
            return 0x84;
        }
        if  (instruction_name=="shl")
        {
            return 0x90;
        }
        if  (instruction_name=="shr")
        {
            return 0x91;
        }
        if  (instruction_name=="ldr")
        {
            return 0xa0;
        }
        if (instruction_name=="str")
        {
            return 0xb0;
        }   
        return -1;
    }

    bool is_relocationable()
    {
        if (op1!=nullptr && dynamic_cast<PCRelOpSym*>(op1)) return true;
        if (op2!=nullptr && dynamic_cast<PCRelOpSym*>(op2)) return true;
        if (op1!=nullptr && dynamic_cast<PCRelOpSymReg*>(op1)) return true;
        if (op2!=nullptr && dynamic_cast<PCRelOpSymReg*>(op2)) return true;
        return false;
    }

    int getSize()
    {
        if (instruction_name=="halt" || instruction_name=="iret" || instruction_name=="ret") return 1;
        else if (instruction_name=="int" || instruction_name=="xchg" || instruction_name=="add" ||
        instruction_name=="sub" || instruction_name=="mul" || instruction_name=="div" || instruction_name=="cmp" ||
        instruction_name=="not" || instruction_name=="and" || instruction_name=="or" || instruction_name=="xor" || instruction_name=="test" ||
        instruction_name=="shl" || instruction_name=="shr" || instruction_name==".word") return 2;
        else if (instruction_name=="pop" || instruction_name=="push") return 3;
        else if (instruction_name==".skip") return ((DirOpLit*)op1)->value;
        else
        {
            bool needs1 = false;
            bool needs2 = false;
            if (op1!=nullptr) needs1=op1->needs_more();
            if (op2!=nullptr) needs2=op2->needs_more();
            if (needs1 || needs2) return 5;
            else return 3;
        }
    }

    vector<char> getRestString()
    {
        vector<char> v;
        if (instruction_name=="int")
        {
            int val = op1->getRegNumber();
            char c = (char)val;
            v.push_back((c<<4)|15);
        }
        else if (instruction_name=="pop" || instruction_name=="push")
        {
            int val = op1->getRegNumber();
            char c = (char)val;
            v.push_back((c<<4)|6);
            if (instruction_name=="pop")
            {
                v.push_back((4<<4)|2);
            }
            else if (instruction_name=="push")
            {
                v.push_back((1<<4)|2);
            }
        }
        else if (instruction_name=="call")
        {
            char a = op1->ABytes();
            int num_reg=0;
            if (a==1 || a==2 || a==3 || a==5) // ima registar
            {
                num_reg = op1->getRegNumber();
            }
            v.push_back((char)((15<<4)|num_reg));
            v.push_back((char)a);
        }
        else if (instruction_name=="jmp" || instruction_name=="jeq" || instruction_name=="jne" || instruction_name=="jgt")
        {
            char a = op1->ABytes();
            int num_reg=0;
            if (a==1 || a==2 || a==3 || a==5) // ima registar
            {
                num_reg = op1->getRegNumber();
            }
            v.push_back((char)((15<<4)|num_reg));
            v.push_back((char)a);
        }
        else if (instruction_name=="xchg" || instruction_name=="add" || instruction_name=="sub" || instruction_name=="mul" || instruction_name=="div" ||
        instruction_name=="cmp" || instruction_name=="shl" || instruction_name=="shr" || instruction_name=="not" || instruction_name=="and" || 
        instruction_name=="or" || instruction_name=="xor" || instruction_name=="test")
        {
            char reg1 = (char)op1->getRegNumber();
            char reg2 = (char)op2->getRegNumber();
            v.push_back((reg1<<4)|reg2);
        }
        else if (instruction_name=="ldr" || instruction_name=="str")
        {
            char a = op2->ABytes();
            int reg1 = op1->getRegNumber();
            int num_reg=0;
            if (a==1 || a==2 || a==3 || a==5) // ima registar
            {
                num_reg = op2->getRegNumber();
            }
            v.push_back((char)((reg1<<4)|num_reg));
            v.push_back((char)a);
        }
        return v;
    }

    vector<char> fix(vector<SectionInfo*>& section_infos,string& section,int loc) // Drugi prolaz
    {
        vector<char> v;
        SectionInfo* si = nullptr;
        for (auto& sis : section_infos)
        {
            if (sis->section_name==section)
            {
                si=sis;
                break;
            }
        }
        int val=0;
        if (getInsCode()!=-1) { v.push_back(getInsCode()); si->myCode.push_back(getInsCode()); }
        if (getSize()==1) return v;
        vector<char> dodString = getRestString();
        for (int i=0;i<(int)dodString.size();i++)
        {
            v.push_back(dodString[i]);
            si->myCode.push_back(dodString[i]);
        }
        if (getSize()!=5 && instruction_name!=".word" && instruction_name!=".skip") return v;
        string symbol="";
        if (instruction_name==".word" || instruction_name==".skip" || instruction_name=="jmp" || instruction_name=="call"
            || instruction_name=="jeq" || instruction_name=="jne" || instruction_name=="jgt") symbol=op1->getSymbol();
        else symbol = op2->getSymbol();
        if (symbol=="") // literal
        {
            if (instruction_name==".word" || instruction_name==".skip" || instruction_name=="jmp" || instruction_name=="call"
            || instruction_name=="jeq" || instruction_name=="jne" || instruction_name=="jgt") val=op1->getValue();
            else val=op2->getValue();
        }
        else // simbol
        {
            SymbolTable* primerak = SymbolTable::getOnlySymbolTable();
            if (!primerak->exists(symbol))
            {
                primerak->addExtern(symbol);
            }
            SymbolTable::Entry* ent = &(primerak->table[symbol]);
            if (primerak->undefined(symbol)) // nije def
            {
                if (ent->section!=section) // u drugoj sekciji - uvek jer nemas pojma sekciju
                {
                    bool is_global = ent->is_global();
                    val=0;
                    if (is_global) val=0;
                    if (is_relocationable()) val-=2;
                    if (is_global) // Uvek globalno jer je nedefinisano
                    {
                        if (instruction_name==".word" || instruction_name==".skip") si->addToRelTable(val,symbol,(is_relocationable()?2:3),loc);
                        else si->addToRelTable(val,symbol,(is_relocationable()?2:1),loc+3);
                    }
                }
            }
            else // definisano
            { 
                if (ent->section!=section) // nisu iste sekcije
                {
                    if (ent->section=="abs") // absolutno
                    {
                        if (is_relocationable()) 
                        {
                            val = primerak->get_val(symbol)-2;
                            si->addToRelTable(val,"abs",2,loc+3);
                        }
                        else val = primerak->get_val(symbol);
                    }
                    else if (!ent->is_global()) // nije global
                    {
                        val=0;
                        if (is_relocationable()) val-=2;
                        val+=primerak->get_val(symbol);
                        if (instruction_name==".word" || instruction_name==".skip") si->addToRelTable(val,ent->section,(is_relocationable()?2:3),loc);
                        else if (is_relocationable() || ent->section!="abs") si->addToRelTable(val,ent->section,(is_relocationable()?2:1),loc+3);
                        //si->print();
                    }
                    else
                    {
                        val=0;
                        if (is_relocationable()) val-=2;
                        if (instruction_name==".word" || instruction_name==".skip") si->addToRelTable(val,symbol,(is_relocationable()?2:3),loc);
                        else if (is_relocationable() || ent->section!="abs") si->addToRelTable(val,symbol,(is_relocationable()?2:1),loc+3);
                    }
                }
                else // iste su sekcije
                {
                    if (is_relocationable())
                    {
                        val = primerak->get_val(symbol)-(loc+getSize());
                    }
                    else
                    {
                        if (!ent->is_global()) // nije global
                        {
                            val=primerak->get_val(symbol);
                            if (instruction_name==".word" || instruction_name==".skip") si->addToRelTable(val,ent->section,(is_relocationable()?2:3),loc);
                            else si->addToRelTable(val,ent->section,1,loc+3);
                        }
                        else // global;
                        {
                            val=0;
                            if (instruction_name==".word" || instruction_name==".skip") si->addToRelTable(val,symbol,(is_relocationable()?2:3),loc);
                            si->addToRelTable(val, symbol, 1,loc+3);
                        }
                    }
                }
            }
        }
        unsigned int val_pom=(unsigned int)val;
        if (instruction_name==".skip")
        {
            for (unsigned int i=0;i<val_pom;i++)
            {
                v.push_back((unsigned char)0);
                si->myCode.push_back((unsigned char)0);
            }
        }
        else
        {
            unsigned char prvi_deo = (unsigned char)(val_pom>>8);
            unsigned char drugi_deo=(unsigned char)(val_pom&0xff);
            if (instruction_name!=".word") // Ako nije word, ispisi normalno
            {
                v.push_back(prvi_deo);
                si->myCode.push_back(prvi_deo);
                v.push_back(drugi_deo);
                si->myCode.push_back(drugi_deo);
            }
            else // Ako jeste word, ispisi kontra
            {
                v.push_back(drugi_deo);
                si->myCode.push_back(drugi_deo);
                v.push_back(prvi_deo);
                si->myCode.push_back(prvi_deo);
            }
        }
        return v;
    }
};

#endif