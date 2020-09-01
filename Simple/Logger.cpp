//---------------------------------------------------//
//                    MIT License                    //
// Copyright @ 2018-2020 Tony Su All Rights Reserved //
//        https://github.com/peitaosu/Logger         //
//---------------------------------------------------//

#include "Logger.h"

namespace Logging {

LogEvent::LogEvent() {
}

LogEvent::LogEvent(LogEventLevel level, std::string message) {
    auto time = std::time(nullptr);
    auto tm = *std::localtime(&time);
    this->timestamp = tm;
    this->level = level;
    this->message = message;
}

std::tm LogEvent::GetTimestamp() {
    return this->timestamp;
}
LogEventLevel LogEvent::GetLevel() {
    return this->level;
}
std::string LogEvent::GetMessage() {
    return this->message;
}


Logger::Logger()
{
}

Logger::~Logger()
{
}

Logger* Logger::Instance() {
    if (!_logger) _logger = new Logger();
    return _logger;
}

void Logger::SetLogPath(std::string log) {
    this->_logPath = log;
}

void Logger::Write(LogEvent logEvent) {
    std::string log;
    std::string level;
    switch (logEvent.GetLevel())
    {
    case LogEventLevel::VERBO:
        level = "VERBO";
        break;
    case LogEventLevel::DEBUG:
        level = "DEBUG";
        break;
    case LogEventLevel::INFOR:
        level = "INFOR";
        break;
    case LogEventLevel::WARNN:
        level = "WARNN";
        break;
    case LogEventLevel::ERROR:
        level = "ERROR";
        break;
    case LogEventLevel::FATAL:
        level = "FATAL";
        break;
    default:
        level = "VERBO";
        break;
        std::ostringstream time_string;
        time_string << std::put_time(&logEvent.GetTimestamp(), "%Y/%m/%d %H:%M:%S");
        log = time_string.str() + ": [" + level + "] " + logEvent.GetMessage();
        int mode = std::ios::out + std::ios::app;
        std::ofstream file(this->_logPath, mode);
        file << log + "\n";
        file.close();

        std::cout << log << std::endl;
    }
}

void Logger::Write(LogEventLevel level, std::string message) {
    Write(LogEvent(level, message));
}

void Logger::Verbose(std::string message) {
    Write(LogEventLevel::VERBO, message);
}

void Logger::Debug(std::string message) {
    Write(LogEventLevel::DEBUG, message);
}

void Logger::Information(std::string message) {
    Write(LogEventLevel::INFOR, message);
}

void Logger::Warning(std::string message) {
    Write(LogEventLevel::WARNN, message);
}

void Logger::Error(std::string message) {
    Write(LogEventLevel::ERROR, message);
}

void Logger::Fatal(std::string message) {
    Write(LogEventLevel::FATAL, message);
}

Logger* Logger::_logger = nullptr;

}