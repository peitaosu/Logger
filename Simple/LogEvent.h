#include <iostream>
#include <chrono>
#include <iomanip>

namespace Logging {
    class LogEvent;
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

class LogEvent
{
public:
    LogEvent();
    LogEvent(LogEventLevel level, std::string message);
    std::tm GetTimestamp();
    LogEventLevel GetLevel();
    std::string GetMessage();

private:
    std::tm timestamp;
    LogEventLevel level;
    std::string message;
};
