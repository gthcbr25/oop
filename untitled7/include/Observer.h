#pragma once

#include <fstream>
#include <iostream>
#include <string>

class EventObserver {
public:
    virtual void handleEvent(const std::string& event) = 0;
    virtual ~EventObserver() = default;
};

class ConsoleObserver : public EventObserver {
public:
    virtual void handleEvent(const std::string& event) override {
        std::cout << event << std::endl;
    }
};

class FileObserver : public EventObserver {
public:
    FileObserver(const std::string& filename) 
        :
        logFile(filename)
    {}
    virtual void handleEvent(const std::string& event) override {
        logFile << event << std::endl;
    }
    ~FileObserver() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
private:
    std::ofstream logFile;
};