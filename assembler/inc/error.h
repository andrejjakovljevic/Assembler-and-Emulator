#ifndef ERROR_H
#define ERROR_H
#include<string>

class Error
{
public:
    string mess;

    Error(string m)
    {
        this->mess=m;
    }
};

#endif