#include <iostream>
#include <string>
#include "LogEvent.h"

namespace Logging {
    class Logger;
}

class Logger
{
public:
    Logger();
    ~Logger();
    static Logger* Instance() {
        if (!_logger) _logger = new Logger();
        return _logger;
    }
    void LoadConfig();
    void LoadConfig(std::string config);
    bool IsEnabled(LogEventLevel level);
    void Write(LogEvent logEvent);
    void Write(LogEventLevel level, std::string message, LogEventException exception);
    void Verbose(std::string message, LogEventException exception);
    void Debug(std::string message, LogEventException exception);
    void Information(std::string message, LogEventException exception);
    void Warning(std::string message, LogEventException exception);
    void Error(std::string message, LogEventException exception);
    void Fatal(std::string message, LogEventException exception);

private:
    static Logger* _logger;
    LogEventLevel _minimalLevel = LogEventLevel::VERBO;
    std::string _defaultConfig = "LogConfig.xml";
};

