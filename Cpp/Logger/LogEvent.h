#include <iostream>
#include <chrono>

namespace Logger {
    class LogEvent;
    class LogEventException;
    enum LogEventLevel;
}

enum LogEventLevel
{
    VERBO,
    DEBUG,
    INFOR,
    WARNN,
    ERROR,
    FATAL
};

class LogEventException
{
public:
    LogEventException();
    LogEventException(std::string summary, std::string detail);

private:
    std::string summary;
    std::string detail;
};

class LogEvent
{
public:
    LogEvent();
    LogEvent(std::chrono::milliseconds timestamp, LogEventLevel level, std::string message, LogEventException exception);

private:
    std::chrono::milliseconds timestamp;
    LogEventLevel level;
    std::string message;
    LogEventException exception;
};
