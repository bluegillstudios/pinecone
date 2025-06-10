#include "Logger.h"
#include <iostream>

namespace Pinecone {

    void Logger::Init() {
        std::cout << "[Logger] Initialized.\n";
    }

    void Logger::Shutdown() {
        std::cout << "[Logger] Shutdown.\n";
    }

    void Logger::Log(LogLevel level, const std::string& message) {
        const char* levelStr = "";
        switch (level) {
            case LogLevel::Trace: levelStr = "TRACE"; break;
            case LogLevel::Info:  levelStr = "INFO "; break;
            case LogLevel::Warn:  levelStr = "WARN "; break;
            case LogLevel::Error: levelStr = "ERROR"; break;
            case LogLevel::Fatal: levelStr = "FATAL"; break;
        }
        std::cout << "[" << levelStr << "] " << message << "\n";
    }

    void Logger::Trace(const std::string& message) { Log(LogLevel::Trace, message); }
    void Logger::Info (const std::string& message) { Log(LogLevel::Info,  message); }
    void Logger::Warn (const std::string& message) { Log(LogLevel::Warn,  message); }
    void Logger::Error(const std::string& message) { Log(LogLevel::Error, message); }
    void Logger::Fatal(const std::string& message) { Log(LogLevel::Fatal, message); }

}
