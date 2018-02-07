#include "Logger.h"

void Logger::SetClass(string className){
    m_className = className;
}

void Logger::Log(string functionName, string toLog){
    cout << "[" << m_className << " (" << functionName << ")] " << toLog << endl;
}