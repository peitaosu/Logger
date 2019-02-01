#include <iostream>
#include <chrono>

namespace Logging {
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
    std::string GetSummary();
    std::string GetDetail();

private:
    std::string summary;
    std::string detail;
};

class LogEvent
{
public:
    LogEvent();
    LogEvent(LogEventLevel level, std::string message);
    LogEvent(LogEventLevel level, std::string message, LogEventException exception);
    std::chrono::milliseconds GetTimestamp();
    LogEventLevel GetLevel();
    std::string GetMessage();
    LogEventException GetException();

private:
    std::chrono::milliseconds timestamp;
    LogEventLevel level;
    std::string message;
    LogEventException exception;
};
