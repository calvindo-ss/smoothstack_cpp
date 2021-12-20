#include <filesystem>
#include <fstream>
#include <ctime>
#include <iostream>

#include <Logging.h>

void Logger::log(std::string log){

    std::ofstream logstring(logfile, std::ios_base::app);

    if(!if_file_exists(logfile)){
    }
    else{
        std::cout << log << std::endl;
        logstring << "\n" << time() + ": " + log;
    }

}

std::string Logger::time(){
    
    time_t rawtime;
    struct tm *timeinfo;

    char buffer [80];

    timeinfo = localtime (&rawtime);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d  %H:%M:%S", timeinfo);

    return buffer;
}

bool Logger::if_file_exists(std::string lfile){
    if (FILE *file = fopen(lfile.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}