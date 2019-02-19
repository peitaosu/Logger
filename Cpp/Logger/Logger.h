#include <iostream>
#include <string>
#include "LogEvent.h"
#include "LogConfig.h"

namespace Logging {
    class Logger;
}

class Logger
{
public:
    Logger();
    ~Logger();
    static Logger* Instance();
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
    LogConfig _config;
    std::string _defaultConfig = "LogConfig.xml";
    bool _fileAppenderEnabled = false;
    bool _consoleAppenderEnabled = false;
    bool _coloredConsoleAppenderEnabled = false;
};

