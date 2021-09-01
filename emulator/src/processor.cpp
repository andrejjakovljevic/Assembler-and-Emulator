#include "processor.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
using namespace chrono;

vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

Processor::Processor()
{
    for (int i=0;i<(1<<15);i++)
    {
        mem[i]=0;
    }
    // set sp to max val;
    reg[6]=0xFFFF;
    lastTime=chrono::high_resolution_clock::now();
}

void Processor::checkTimer()
{
    auto now = chrono::high_resolution_clock::now();
    unsigned short val = getNumFromAddres(0xFF10); // za duzinu
    int dur = -1;
    if (val==0) dur=500;
    else if (val==1) dur=1000;
    else if (val==2) dur=1500;
    else if (val==3) dur=2000;
    else if (val==4) dur=5000;
    else if (val==5) dur=10000;
    else if (val==6) dur=30000;
    else if (val==7) dur=60000;
    auto difference = duration_cast<milliseconds>(now - lastTime);
    //cout << "diff=" << difference.count() << endl;
    if (difference.count()>=dur)
    {
        interrupts[2]=true;
        lastTime=now;
    }
}

void Processor::populateMemory(string filename)
{
    ifstream inputFile;
    inputFile.open(filename);
    while(inputFile.peek() != EOF)
    {
        string help;
        getline(inputFile,help);
        vector<string> prva_podela = split(help,":");
        int mem_pos = stoi(prva_podela[0].c_str(),nullptr,16);
        vector<string> podaci = split(prva_podela[1]," ");
        for (int i=0;i<min(8,(int)podaci.size());i++)
        {
            mem[mem_pos+i]=stoi(podaci[i],nullptr,16);
        }
    }
}

unsigned short Processor::findStart()
{
    return getNumFromAddres(0);
}

unsigned char Processor::takeNext()
{
    unsigned short byte = mem[reg[7]];
    reg[7]++;
    return byte;
}

void Processor::wrongOpCode()
{
    interrupts[1]=true;
}

void Processor::printIfNeeded()
{
    if (mem[0xFF00]!=0 || mem[0xFF01]!=0)
    {
        cout << (char)(getNumFromAddres(0xFF00)) << flush;
        mem[0xFF00]=0;
        mem[0xFF01]=0;
    }
}

void Processor::processInterrupts()
{
    if (is_in_interrupt) return;
    for (int i=0;i<8;i++)
    {
        if (i==2 && (reg[8]&(1<<mask_tr))) continue;
        if (i==3 && (reg[8]&(1<<mask_tl))) continue; 
        if (interrupts[i] && (!(reg[8]&(1<<mask_i))))
        {
            unsigned short memoryPosition = i*2;
            push(reg[7]);
            push(reg[8]);
            reg[7] = getNumFromAddres(memoryPosition);
            //cout << "pc=" << reg[7] << endl; 
            interrupts[i]=0;
            is_in_interrupt=true;
            break;
        }
    }
}

unsigned short Processor::findVal(unsigned char drugi_bajt,unsigned char bajtic)
{
    unsigned char nacin_adresiranja = bajtic&0xf;
    unsigned char up = (bajtic>>4)&0xf;
    if (nacin_adresiranja==0) // neposredno
    {
        unsigned char visa_vrednost=takeNext();
        unsigned char niza_vrednost=takeNext();
        unsigned short val = (visa_vrednost<<8)|niza_vrednost;
        return val;
    }
    else if (nacin_adresiranja==1) // regdir
    {
        unsigned char registar = drugi_bajt&0xf;
        unsigned short k=reg[registar];
        return k;
    }
    else if (nacin_adresiranja==2) // regindbezpom
    {
        unsigned char registar = drugi_bajt&0xf;
        unsigned short k=reg[registar];
        if (up==1)
        {
            reg[registar]-=2;
            k-=2;
        }
        if (up==2)
        {
            reg[registar]+=2;
            k+=2;
        }
        if (up==3)
        {
            reg[registar]-=2;
        }
        if (up==4)
        {
            reg[registar]+=2;
        }
        return getNumFromAddres(k);
    }
    else if (nacin_adresiranja==3) // regind sa pomerajem
    {
        unsigned char visa_vrednost=takeNext();
        unsigned char niza_vrednost=takeNext();
        unsigned short val = (visa_vrednost<<8)|niza_vrednost;
        unsigned char registar = drugi_bajt&0xf;
        unsigned short k=reg[registar];
        if (up==1)
        {
            reg[registar]-=2;
            k-=2;
        }
        if (up==2)
        {
            reg[registar]+=2;
            k+=2;
        }
        if (up==3)
        {
            reg[registar]-=2;
        }
        if (up==4)
        {
            reg[registar]+=2;
        }
        return getNumFromAddres(k+val);
    }
    else if (nacin_adresiranja==4) // memorijsko
    {
        unsigned char visa_vrednost=takeNext();
        unsigned char niza_vrednost=takeNext();
        unsigned short val = (visa_vrednost<<8)|niza_vrednost;
        return getNumFromAddres(val);
    }   
    else if (nacin_adresiranja==5) // reg direktno sa pomerajem
    {
        unsigned char visa_vrednost=takeNext();
        unsigned char niza_vrednost=takeNext();
        unsigned short val = (visa_vrednost<<8)|niza_vrednost;
        unsigned char registar = drugi_bajt&0xf;
        unsigned short k=reg[registar];
        return k+val;
    }
    else wrongOpCode();
    return 0;
}

void Processor::push(unsigned short val)
{
    unsigned char veci = (val>>8)&0xff;
    unsigned char manji = val&0xff;
    reg[6]--;
    mem[reg[6]]=veci;
    reg[6]--;
    mem[reg[6]]=manji;
}

unsigned short Processor::pop()
{
    unsigned short val = getNumFromAddres(reg[6]);
    reg[6]+=2;
    return val;
}

void Processor::doInstruction()
{
    // get ins code
    unsigned char first_byte = takeNext();
    unsigned char prva_cetiri = (first_byte>>4)&0xf;
    if (prva_cetiri==0) // halt
    {
        end=true;
    }
    else if (prva_cetiri==1) // int
    {
        unsigned char second_byte = takeNext();
        unsigned char registar = (second_byte>>4)&0xf;
        interrupts[(reg[registar]%8)]=true;
    }
    else if (prva_cetiri==2) // iret
    {
        reg[8]=pop();
        reg[7]=pop();
        is_in_interrupt=false;
    }
    else if (prva_cetiri==3) // poziv potprograma
    {
        unsigned char second_byte = takeNext();
        unsigned char bajtic = takeNext();
        unsigned short val = findVal(second_byte,bajtic);
        if (interrupts[1]) return;
        push(reg[7]);
        reg[7]=val;
    }
    else if (prva_cetiri==4) // ret
    {
        reg[7]=pop();
    }
    else if (prva_cetiri==5) // skokovi
    {
        unsigned char drugi_bajt = takeNext();
        unsigned char adresiranja_i_tako_to = takeNext();
        unsigned short val = findVal(drugi_bajt,adresiranja_i_tako_to);
        if (interrupts[1]) return;
        unsigned char druga_cetiri=first_byte&0xf;
        if (druga_cetiri==0) // jmp
        {
            reg[7]=val;
        }
        else if (druga_cetiri==1) // jeq
        {
            if (reg[8]&(1<<mask_z)) reg[7]=val;
        }
        else if (druga_cetiri==2) // jne
        {
            if (!(reg[8]&(1<<mask_z))) reg[7]=val;
        }
        else if (druga_cetiri==3) // jgt
        {
            if (!(reg[8]&(1<<mask_n))) reg[7]=val;
        }
        else wrongOpCode();
    }
    else if (prva_cetiri==6) // zamena
    {
        unsigned char second_byte = takeNext();
        unsigned char registar1 = (second_byte>>4)&0xf;
        unsigned char registar2 = second_byte&0xf;
        unsigned short temp = reg[registar1];
        reg[registar1] = reg[registar2];
        reg[registar2] = temp;
    }
    else if (prva_cetiri==7) // aritmeticke
    {
        unsigned char druga_cetiri=first_byte&0xf;
        unsigned char second_byte = takeNext();
        unsigned char registar1 = (second_byte>>4)&0xf;
        unsigned char registar2 = second_byte&0xf;
        if (druga_cetiri==0) // plus
        {
            reg[registar1]+=reg[registar2];
        }
        else if (druga_cetiri==1) // minus
        {
            reg[registar1]-=reg[registar2];
        }
        else if (druga_cetiri==2) // puta
        {
            reg[registar1]*=reg[registar2];
        }
        else if (druga_cetiri==3) // div
        {
            reg[registar1]/=reg[registar2];
        }
        else if (druga_cetiri==4) // cmp
        {
            short temp = reg[registar1]-reg[registar2];
            reg[8]&=0xfff0; // reset psw flags
            if ((short)reg[registar1]>0 && (short)reg[registar2]<0 && temp<0)
            {
                reg[8]|=1<<mask_o;
            }
            if (temp==0)
            {
                reg[8]|=1<<mask_z;
            }
            if (temp<0)
            {
                reg[8]|=1<<mask_n;
            }
        }
        else wrongOpCode();
    }
    else if (prva_cetiri==8) // logicke
    {
        unsigned char druga_cetiri=first_byte&0xf;
        unsigned char second_byte = takeNext();
        unsigned char registar1 = (second_byte>>4)&0xf;
        unsigned char registar2 = second_byte&0xf;
        if (druga_cetiri==0) // not
        {
            reg[registar1]=~reg[registar1];
        }
        else if (druga_cetiri==1) // and
        {
            reg[registar1]&=reg[registar2];
        }
        else if (druga_cetiri==2) // or
        {
            reg[registar1]|=reg[registar2];
        }
        else if (druga_cetiri==3) // xor
        {
            reg[registar1]^=reg[registar2];
        }
        else if (druga_cetiri==4) // test
        {
            reg[8]&=0xfff6; // reset psw flags
            short temp = reg[registar1]&reg[registar2];
            if (temp==0)
            {
                reg[8]|=1<<mask_z;
            }
            if (temp<0)
            {
                reg[8]|=1<<mask_n;
            }
        }
        else wrongOpCode();
    }
    else if (prva_cetiri==9) // pomeranja
    {
        unsigned char druga_cetiri=first_byte&0xf;
        unsigned char second_byte = takeNext();
        unsigned char registar1 = (second_byte>>4)&0xf;
        unsigned char registar2 = second_byte&0xf;
        reg[8]&=0xfff2; // reset psw flags
        if (druga_cetiri==0) // left shift
        {
            bool is_carry=false;
            for (int i=0;i<reg[registar2];i++)
            {
                if ((reg[registar1]&(1<<15))!=0) is_carry=true;
                reg[registar1]<<=1;
                if (reg[registar1]==0) break;
            }
            if (is_carry)
            {
                reg[8]|=1<<mask_c;
            }
            if (reg[registar1]==0)
            {
                reg[8]|=1<<mask_z;
            }
            if ((short)(reg[registar1])<0)
            {
                reg[8]|=1<<mask_n;
            }
        }
        else if (druga_cetiri==1) // right shift
        {
            bool is_carry=false;
            for (int i=0;i<reg[registar2];i++)
            {
                if ((reg[registar1]&(1<<15))!=0) is_carry=true;
                reg[registar1]>>=1;
                if (reg[registar1]==0) break;
            }
            if (is_carry)
            {
                reg[8]|=1<<mask_c;
            }
            if (reg[registar1]==0)
            {
                reg[8]|=1<<mask_z;
            }
            if ((short)(reg[registar1])<0)
            {
                reg[8]|=1<<mask_n;
            }
        }
        else wrongOpCode();
    }
    else if (prva_cetiri==10) // load
    {
        //cout << "pc=" << (int)reg[7] << endl;
        unsigned char drugi_bajt = takeNext();
        unsigned char adresiranja_i_tako_to = takeNext();
        unsigned short val = findVal(drugi_bajt,adresiranja_i_tako_to);
        unsigned char registar1 = (drugi_bajt>>4)&0xf;
        reg[registar1]=val;
    }
    else if (prva_cetiri==11) // store
    {
        unsigned char drugi_bajt = takeNext();
        unsigned char bajtic = takeNext();
        unsigned char nacin_adresiranja = bajtic&0xf;
        unsigned char up = (bajtic>>4)&0xf;
        unsigned short ono_sto_upisujemo = (drugi_bajt>>4)&0xf;
        if (nacin_adresiranja==0) // neposredno
        {
            wrongOpCode();
        }
        else if (nacin_adresiranja==1) // regdir
        {
            unsigned char registar = drugi_bajt&0xf;
            reg[registar]=reg[ono_sto_upisujemo];
        }
        else if (nacin_adresiranja==2) // regindbezpom
        {
            unsigned char registar = drugi_bajt&0xf;
            unsigned short k=reg[registar];
            if (up==1)
            {
                reg[registar]-=2;
                k-=2;
            }
            if (up==2)
            {
                reg[registar]+=2;
                k+=2;
            }
            if (up==3)
            {
                reg[registar]-=2;
            }
            if (up==4)
            {
                reg[registar]+=2;
            }
            mem[k]=reg[ono_sto_upisujemo]&0xff;
            mem[k+1]=(reg[ono_sto_upisujemo]>>8)&0xff;
        }
        else if (nacin_adresiranja==3) // regind sa pomerajem
        {
            unsigned char visa_vrednost=takeNext();
            unsigned char niza_vrednost=takeNext();
            unsigned short val = (visa_vrednost<<8)|niza_vrednost;
            unsigned char registar = drugi_bajt&0xf;
            unsigned short k=reg[registar];
            if (up==1)
            {
                reg[registar]-=2;
                k-=2;
            }
            if (up==2)
            {
                reg[registar]+=2;
                k+=2;
            }
            if (up==3)
            {
                reg[registar]-=2;
            }
            if (up==4)
            {
                reg[registar]+=2;
            }
            mem[k+val]=reg[ono_sto_upisujemo]&0xff;
            mem[k+1+val]=(reg[ono_sto_upisujemo]>>8)&0xff;
        }
        else if (nacin_adresiranja==4) // memorijsko
        {
            unsigned char visa_vrednost=takeNext();
            unsigned char niza_vrednost=takeNext();
            unsigned short val = (visa_vrednost<<8)|niza_vrednost;
            //cout << "val=" << val << endl;
            //cout << "reg=" << (int)reg[ono_sto_upisujemo] << endl;
            //cout << "gdb=" << (int)mem[0xFF02] << endl;
            mem[val]=reg[ono_sto_upisujemo]&0xff;
            mem[1+val]=(reg[ono_sto_upisujemo]>>8)&0xff;
        }
        else wrongOpCode();
    }
}