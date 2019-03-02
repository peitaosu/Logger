//---------------------------------------------------//
//                    MIT License                    //
// Copyright @ 2018-2019 Tony Su All Rights Reserved //
//        https://github.com/peitaosu/Logger         //
//---------------------------------------------------//

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <regex>
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
    void SetLogPath(std::string log);
    bool IsEnabled(LogEventLevel level);
    void Write(LogEvent logEvent);
    void Write(LogEventLevel level, std::string message);
    void Write(LogEventLevel level, std::string message, LogEventException exception);
    void Verbose(std::string message);
    void Verbose(std::string message, LogEventException exception);
    void Debug(std::string message);
    void Debug(std::string message, LogEventException exception);
    void Information(std::string message);
    void Information(std::string message, LogEventException exception);
    void Warning(std::string message);
    void Warning(std::string message, LogEventException exception);
    void Error(std::string message);
    void Error(std::string message, LogEventException exception);
    void Fatal(std::string message);
    void Fatal(std::string message, LogEventException exception);

private:
    static Logger* _logger;
    LogEventLevel _minimalLevel = LogEventLevel::VERBO;
    LogConfig _config;
    std::string _defaultConfig = "LogConfig.xml";
    std::string _logPath = "Logger.log";
};

