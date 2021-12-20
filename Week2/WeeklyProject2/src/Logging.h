#pragma once
#include <fstream>

class Logger{
    public:
        Logger():
        logfile("logfile.log"){};

        void log(std::string);

    private:
        std::string logfile;

        std::string time();
        bool if_file_exists(std::string);

};