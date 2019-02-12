#include "Logger.h"

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::LoadConfig() {

}

void Logger::LoadConfig(std::string config) {

}

bool Logger::IsEnabled(LogEventLevel level) {
    if(level >= this->_minimalLevel)
    {
        return true;
    }
    return false;
}

void Logger::Write(LogEvent logEvent) {
    std::string log = "";
    log += "[";
    log += logEvent.GetTimestamp().count();
    log += "] [";
    log += logEvent.GetLevel();
    log += "] ";
    log += logEvent.GetMessage();
    if (logEvent.GetException().GetSummary() != "") {
        log += logEvent.GetException().GetSummary();
    }
    std::cout << log << std::endl;
}

void Logger::Write(LogEventLevel level, std::string message, LogEventException exception) {
    if(IsEnabled(level))
        Write(LogEvent(level, message, exception));
}

void Logger::Verbose(std::string message, LogEventException exception) {
    Write(LogEventLevel::VERBO, message, exception);
}

void Logger::Debug(std::string message, LogEventException exception) {
    Write(LogEventLevel::DEBUG, message, exception);
}

void Logger::Information(std::string message, LogEventException exception) {
    Write(LogEventLevel::INFOR, message, exception);
}

void Logger::Warning(std::string message, LogEventException exception) {
    Write(LogEventLevel::WARNN, message, exception);
}

void Logger::Error(std::string message, LogEventException exception) {
    Write(LogEventLevel::ERROR, message, exception);
}

void Logger::Fatal(std::string message, LogEventException exception) {
    Write(LogEventLevel::FATAL, message, exception);
}

Logger* Logger::_logger = nullptr;

