#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "LogEvent.h"

namespace Logging {
    class Logger;
}

class Logger
{
public:
    Logger();
    ~Logger();
    static Logger* Instance();
    void SetLogPath(std::string log);
    void Write(LogEvent logEvent);
    void Write(LogEventLevel level, std::string message);
    void Verbose(std::string message);
    void Debug(std::string message);
    void Information(std::string message);
    void Warning(std::string message);
    void Error(std::string message);
    void Fatal(std::string message);

private:
    static Logger* _logger;
    std::string _logPath = "Logger.log";
};

