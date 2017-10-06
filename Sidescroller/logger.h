#pragma once
#include <fstream>
#include <string>
#include "time.h"
#include <iostream>
//using namespace std;
class Log {
public:
    Log();
    Log(const Log&);
    ~Log();
    Log(std::string);
    void openFile(std::string fileName, std::fstream::openmode mode = std::fstream::in | std::fstream::out | std::fstream::trunc);
    void closeFile();
    void writeMessage(std::string msg);

private:
    std::fstream logFile;
    std::string fileName;
};

