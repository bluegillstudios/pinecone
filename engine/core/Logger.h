#pragma once

#include <string>

namespace Pinecone {

    enum class LogLevel {
        Trace,
        Info,
        Warn,
        Error,
        Fatal
    };

    class Logger {
    public:
        static void Init();
        static void Shutdown();

        static void Log(LogLevel level, const std::string& message);
        static void Trace(const std::string& message);
        static void Info(const std::string& message);
        static void Warn(const std::string& message);
        static void Error(const std::string& message);
        static void Fatal(const std::string& message);
    };

}
