#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>
#include <iostream>

void log(const std::string& message) {
    std::ofstream log_file("pipeline_log.txt", std::ios::app);
    if (log_file.is_open()) {
        log_file << message << std::endl;
        log_file.close();
    }
    else {
        std::cerr << "Unable to open log file." << std::endl;
    }
}

#endif // LOG_H