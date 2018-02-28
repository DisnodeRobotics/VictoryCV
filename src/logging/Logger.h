#ifndef Included_Logger_H
#define Included_Logger_H
#include <iostream>
#include <string.h>
#include "../termcolor/termcolor.hpp"
using namespace std;
class Logger{
    private:
        string m_className = "GenericClass";
    public:
        void SetClass(string className);
        
        void Info(string functionName, string toLog);
        void Warning(string functionName, string toLog);
        void Error(string functionName, string toLog);
        void Success(string functionName, string toLog);
};
#endif 