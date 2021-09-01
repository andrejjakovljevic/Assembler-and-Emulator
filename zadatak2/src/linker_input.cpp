#include "linker_input.h"
#include <string>
#include <algorithm>
using namespace std;

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

LinkerInput::LinkerInput(string filename)
{
    ifstream inputFile;
    inputFile.open(filename);
    int br=0;
    int poz=0;
    bool is_simbol=false;
    bool is_sekcije=false;
    bool is_kod = false;
    bool is_ime = false;
    bool is_reloc=false;
    while(inputFile.peek() != EOF)
    {
        string help;
        getline(inputFile,help);
        if (br<2) { br++; continue; }
        if (br==2 && help!="-------------------SEKCIJE----------------------")
        {
            is_simbol=true;
        }
        else if (help=="-------------------SEKCIJE----------------------") 
        {
            is_simbol=false;
            is_sekcije=true;
        }
        else if (help=="----------IZGLED PROGRAMA---------------")
        {
            is_simbol=false;
            is_sekcije=false;
            is_kod=true;
            poz=0;
        }
        if (is_simbol)
        {
            vector<string> v = split(help," ");
            string ime = v[0];
            // 1- local; 2-global; 3-section
            int k;
            if (v[1]=="L") k=1;
            else if (v[1]=="G") k=2;
            else k=3;
            string section = v[2];
            if (v.size()==4) section="";
            int val;
            if (v.size()==4) val = atoi(v[2].c_str());
            else val = atoi(v[3].c_str());
            bool is_undef=false;
            if (v.size()==4 && v[3]=="NE") is_undef=true;
            else if (v[4]=="NE") is_undef=true;
            st.addLinkerEntry(ime,k,section,val,is_undef);
        }
        else if (is_sekcije)
        {
            if (help.substr(0,18)=="Ime       Velicina") 
            {
                is_ime=true;
                is_reloc=false;
            }
            else if (is_ime)
            {
                vector<string> v = split(help," ");
                SectionInfo sis(v[0],atoi(v[2].c_str()));
                sis.set_size(atoi(v[1].c_str()));
                si.push_back(sis);
                is_ime=false;
            }
            else if (help=="relokacioni info:")
            {
                is_reloc=true;
            }
            else if (is_reloc)
            {
                vector<string> v = split(help," ");
                if (v.size()==4 && v[0]!="Addend")
                {
                    int relok = 1;
                    if (v[2]=="PC_16") relok=2;
                    if (v[2]=="DIR_16_R") relok=3;
                    si[si.size()-1].addToRelTable(atoi(v[0].c_str()),v[1],relok,atoi(v[3].c_str()));
                }
            }
        }
        else if (is_kod && help!="----------IZGLED PROGRAMA---------------") 
        {
            if (help[0]=='-') break;
            vector<string> v = split(help," ");
            for (auto& k : v)
            {
                si[poz].myCode.push_back((unsigned char)stoi(k,nullptr,16));
            }
            poz++;
        }
        br++;
    }
}

int LinkerInput::findSizeOfSecition(string section)
{
    for (int i=0;i<(int)si.size();i++)
    {
        auto& poz = si[i];
        if (poz.section_name==section)
        {
            return poz.size;
        }
    }
    return -1;
}

int LinkerInput::getSectionInfoPos(string section)
{
    for (int i=0;i<(int)si.size();i++)
    {
        auto& poz = si[i];
        if (poz.section_name==section)
        {
            return i;
        }
    }
    // Dummy ne bi trebalo nikad dodje do ovde
    return -1;
}

void LinkerInput::mergeLinkerInputs(LinkerInput li)
{
    // Prvo ne sekcije
    for (auto& ulaz : li.st.table)
    {
        string ime = ulaz.first;
        if (ime=="abs") continue;
        SymbolTable::Entry u = ulaz.second;
        string sekcija = u.section;
        if (u.type!=3) // nije sekcija
        {   
            if (st.exists(ime) && st.table[ime].is_undefined==false && li.st.table[ime].is_undefined==false) // Postoji definisan - Greska!
            {
                cout << "Error, double definition of symbol:" << ime << endl;
                exit(-1);
            }
            if (st.exists(ime) && st.table[ime].is_undefined && li.st.table[ime].is_undefined==false) // Postoji nedfinisan - obrisi, svakako ces ga dodati!!!
            {
                st.table.erase(ime);
            }
            else if (li.st.table[ime].is_undefined && !st.exists(ime)) // nije definisano
            {
                st.addExtern(ime);
            }
            if (li.st.table[ime].is_undefined==false) // definisano
            {
                if (st.exists(sekcija) && st.table[sekcija].type==3) // postoji njegova sekcija, dodaj u sekciju, pa u tabelu
                {
                    st.addLinkerEntry(ulaz.first,ulaz.second.type,ulaz.second.section,ulaz.second.value+findSizeOfSecition(sekcija),ulaz.second.is_undefined);
                }
                else // ne postoji njegova sekcija
                {
                    st.addLinkerEntry(ulaz.first,ulaz.second.type,ulaz.second.section,ulaz.second.value,ulaz.second.is_undefined);
                }
            }
        }
    }
    // Sredi relokacije pre sekcija
    for (auto& ulaz : li.st.table)
    {
        string ime = ulaz.first;
        SymbolTable::Entry u = ulaz.second;
        string sekcija = u.section;
        if (st.exists(ime) && u.type==3)
        {
            int k = getSectionInfoPos(ime);
            for (auto& ulazUTabeluRelokacija : li.si[li.getSectionInfoPos(ime)].rel_table.table)
            {
                for (auto& ulazPoSimbolu : ulazUTabeluRelokacija.second)
                {
                    string oslanjac = ulazPoSimbolu.symbol;
                    int vr = ulazPoSimbolu.addend;
                    // Ako je relokacioni zapis za sekciju koja vec postoji
                    if (getSectionInfoPos(oslanjac)!=-1)
                    {
                        vr+=findSizeOfSecition(oslanjac);
                    }
                    si[k].addToRelTable(vr,ulazPoSimbolu.symbol,ulazPoSimbolu.type,ulazPoSimbolu.offset+findSizeOfSecition(ime));
                }
            }
        }
    }
    // Drugo sekcije
    for (auto& ulaz : li.st.table)
    {
        string ime = ulaz.first;
        SymbolTable::Entry u = ulaz.second;
        string sekcija = u.section;
        if (u.type==3) // jeste sekcija
        {
            if (!st.exists(ime)) // sekcija ne postoji
            {
                st.addSection(ime); // Dodaj u tabelu
                // Dodaj relokacioni
                si.push_back(li.si[li.getSectionInfoPos(ime)]);
            }
            else // Sekcija postoji
            {
                int k = getSectionInfoPos(ime);
                // Dodaj velicinu
                si[k].size+=li.si[li.getSectionInfoPos(ime)].size;
                // Spoj kodove sekcija
                for (int i=0;i<(int)li.si[li.getSectionInfoPos(ime)].myCode.size();i++)
                {
                    si[k].myCode.push_back(li.si[li.getSectionInfoPos(ime)].myCode[i]);
                }
            }
        }
    }
    // Resi relokacione koje mogu se rese
    for (int i=0;i<(int)si.size();i++)
    {
        SectionInfo& sectionInfo = si[i];
        for (auto& entry : sectionInfo.rel_table.table)
        {
            string name = entry.first;
            vector<int> zaIzbac;
            int givenPosition=0;
            for (auto& e : entry.second)
            {
                if (st.table[e.symbol].section==sectionInfo.section_name && e.type==2) // U istoj su sekciji  i relokaciono je
                {
                    int val = st.table[e.symbol].value-e.offset+e.addend;
                    unsigned int val_pom=(unsigned int)val;
                    unsigned char prvi_deo = (unsigned char)(val_pom>>8);
                    unsigned char drugi_deo=(unsigned char)(val_pom&0xff);
                    sectionInfo.myCode[e.offset]=prvi_deo;
                    sectionInfo.myCode[e.offset+1]=drugi_deo;
                    zaIzbac.push_back(givenPosition);
                    givenPosition++;
                }
                else if (st.table[e.symbol].section=="abs" && (e.type==1 || e.type==3)) // ovaj je apsolutni
                {
                    int val = st.table[e.symbol].value+e.addend;
                    unsigned int val_pom=(unsigned int)val;
                    unsigned char prvi_deo = (unsigned char)(val_pom>>8);
                    unsigned char drugi_deo=(unsigned char)(val_pom&0xff);
                    if (e.type==1) // obicno_direktno
                    {
                        sectionInfo.myCode[e.offset]=prvi_deo;
                        sectionInfo.myCode[e.offset+1]=drugi_deo;
                    }
                    else if (e.type==3) // kontra_direktno
                    {
                        sectionInfo.myCode[e.offset]=drugi_deo;
                        sectionInfo.myCode[e.offset+1]=prvi_deo;
                    }
                    zaIzbac.push_back(givenPosition);
                    givenPosition++;
                }
                else givenPosition++;
            }
            for (int j=0;j<(int)zaIzbac.size();j++)
            {
                entry.second.erase(entry.second.begin()+zaIzbac[j]);
            }
        }
    }
}

void LinkerInput::checkIsOkay(map<string,long>& places)
{
    for (auto& place : places)
    {
        string sectionName = place.first;
        int size = findSizeOfSecition(sectionName);
        int offset = place.second;
        for (auto& sectioninfo : si)
        {
            if (sectionName==sectioninfo.section_name) continue;
            if (places.find(sectioninfo.section_name)==places.end()) continue;
            int poc1=offset;
            int kraj1=offset+size;
            int poc2=places[sectioninfo.section_name];
            int kraj2=poc2+si[getSectionInfoPos(sectioninfo.section_name)].size;
            if (kraj1>poc2 && kraj1<kraj2) 
            {
                cout << "Overlapping sections: " << sectionName << " and "  << sectioninfo.section_name << endl;
                exit(-1);
            }
            if (kraj2>poc1 && kraj2<kraj1) 
            {
                cout << "Overlapping sections: " << sectionName << " and "  << sectioninfo.section_name << endl;
                exit(-1);
            }
        }
    }
}

void LinkerInput::fixStarts(map<string,long>& places)
{
    int maxval=0;
    // Popravi one u places
    for (auto& sectioninfo : si)
    {
        if (places.find(sectioninfo.section_name)!=places.end())
        {
            sectioninfo.offset=places[sectioninfo.section_name];
            if (sectioninfo.offset+sectioninfo.size>maxval) maxval=sectioninfo.offset+sectioninfo.size;
        }
    }
    // Popravi one van places
    for (auto& sectioninfo : si)
    {
        if (places.find(sectioninfo.section_name)==places.end())
        {
            sectioninfo.offset=maxval;
            maxval+=sectioninfo.size;
        }
    }
}

void LinkerInput::fixReallocation()
{
    for (auto& sectioninfo : si)
    {
        for (auto& reallocation : sectioninfo.rel_table.table)
        {
            for (auto& realokacija : reallocation.second)
            {
                string sekcijaSimbolaKojiSeReferise = st.table[realokacija.symbol].section; 
                if (st.table[realokacija.symbol].is_undefined)
                {
                    cout << "Symbol: " << realokacija.symbol << " is_undefined" << endl;
                    exit(-1); 
                }
                int vrednostNaKojuSeRef = (sekcijaSimbolaKojiSeReferise=="abs")?st.table[realokacija.symbol].value:st.table[realokacija.symbol].value+si[getSectionInfoPos(sekcijaSimbolaKojiSeReferise)].offset;
                int vrednostKojuOcemo = realokacija.offset+sectioninfo.offset;
                int val;
                if (realokacija.type==1 || realokacija.type==3) // direktno
                {
                    val=vrednostNaKojuSeRef+realokacija.addend;
                }
                else // relativno
                {
                    val=vrednostNaKojuSeRef-vrednostKojuOcemo+realokacija.addend;
                }
                unsigned int val_pom=(unsigned int)val;
                unsigned char prvi_deo = (unsigned char)(val_pom>>8);
                unsigned char drugi_deo=(unsigned char)(val_pom&0xff);
                if (realokacija.type==3) // kontra
                {
                    sectioninfo.myCode[realokacija.offset+1]=prvi_deo;
                    sectioninfo.myCode[realokacija.offset]=drugi_deo;
                }
                else
                {
                    sectioninfo.myCode[realokacija.offset]=prvi_deo;
                    sectioninfo.myCode[realokacija.offset+1]=drugi_deo;
                }
            }
        }
    }
}

int compare(SectionInfo si1, SectionInfo si2)
{
    return si1.offset-si2.offset;
}

void LinkerInput::dumpHex(ofstream& myfile)
{
    sort(si.begin(),si.end(),compare);
    vector<pair<int,unsigned char>> izgledPrograma;
    map<int,bool> postoji;
    for (auto& sectioninfo : si)
    {
        for (int i=0;i<(int)sectioninfo.myCode.size();i++)
        {
            izgledPrograma.push_back(make_pair(sectioninfo.offset+i,sectioninfo.myCode[i]));
            postoji[sectioninfo.offset+i]=true;
        }
    }
    sort(izgledPrograma.begin(),izgledPrograma.end());
    for (int i=0;i<(int)izgledPrograma.size();i++)
    {
        int poz = izgledPrograma[i].first;
        if (poz%8==0) // novi red
        {
            if (i!=0) myfile << endl;
            myfile << right << hex << setfill('0') << setw(4) << uppercase << +(unsigned short)(poz);
            myfile << ": ";
        }
        else if (postoji.find((poz/8)*8)==postoji.end()) // ne postoji donji
        {
            postoji[(poz/8)*8]=true;
            if (i!=0) myfile << endl;
            myfile << right << hex << setfill('0') << setw(4) << uppercase << +(unsigned short)((poz/8)*8);
            myfile << ": ";
            for (int j=(poz/8)*8;j<poz;j++)
            {
                myfile << "00 ";
            }
        }
        myfile << right << hex << setfill('0') << setw(2) << uppercase << +(unsigned char)(izgledPrograma[i].second) << " ";
    }
    myfile << std::dec;
}