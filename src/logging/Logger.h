#include <iostream>
#include <string.h>
using namespace std;
class Logger{
    private:
        string m_className = "GenericClass";
    public:
        void SetClass(string className);
        
        void Log(string functionName, string toLog);
};