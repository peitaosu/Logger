//---------------------------------------------------//
//                    MIT License                    //
// Copyright @ 2018-2020 Tony Su All Rights Reserved //
//        https://github.com/peitaosu/Logger         //
//---------------------------------------------------//

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <chrono>

namespace Logging {

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

}
