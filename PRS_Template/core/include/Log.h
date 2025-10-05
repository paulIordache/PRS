#ifndef LAB_1_LOG_H
#define LAB_1_LOG_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class Log {
public:
    explicit Log(const std::string &filename) {
        logFile.open(filename, std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "Error opening log file." << std::endl;
        }
    }

    ~Log() { logFile.close(); }

    void log(const LogLevel level, const std::string &message) {
        const time_t now = time(nullptr);
        const tm *time_info = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp),
                 "%Y-%m-%d %H:%M:%S", time_info);

        std::ostringstream logEntry;
        logEntry << "[" << timestamp << "] "
                << levelToString(level) << ": " << message
                << std::endl;

        std::cout << logEntry.str();

        if (logFile.is_open()) {
            logFile << logEntry.str();
            logFile
                    .flush();
        }
    }

private:
    std::ofstream logFile;

    static std::string levelToString(const LogLevel level) {
        switch (level) {
            case DEBUG:
                return "DEBUG";
            case INFO:
                return "INFO";
            case WARNING:
                return "WARNING";
            case ERROR:
                return "ERROR";
            case CRITICAL:
                return "CRITICAL";
            default:
                return "UNKNOWN";
        }
    }
};

#endif
