#include "Logger.h"

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

void Logger::LoadConfig() {
    LoadConfig(this->_defaultConfig);
}

void Logger::LoadConfig(std::string config) {
    this->_config = LogConfig(config);
    if (this->_config.GetLogRoot().MinLevel.Value == "VERBO") this->_minimalLevel = LogEventLevel::VERBO;
    if (this->_config.GetLogRoot().MinLevel.Value == "DEBUG") this->_minimalLevel = LogEventLevel::DEBUG;
    if (this->_config.GetLogRoot().MinLevel.Value == "INFOR") this->_minimalLevel = LogEventLevel::INFOR;
    if (this->_config.GetLogRoot().MinLevel.Value == "WARNN") this->_minimalLevel = LogEventLevel::WARNN;
    if (this->_config.GetLogRoot().MinLevel.Value == "ERROR") this->_minimalLevel = LogEventLevel::ERROR;
    if (this->_config.GetLogRoot().MinLevel.Value == "FATAL") this->_minimalLevel = LogEventLevel::FATAL;
}

bool Logger::IsEnabled(LogEventLevel level) {
    if(level >= this->_minimalLevel)
    {
        return true;
    }
    return false;
}

void Logger::Write(LogEvent logEvent) {
    for (auto& appender : this->_config.GetLogAppenders()) {
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
        if (appender.Type == "FileAppender") {
            if (appender.Enabled) {
                int mode = std::ios::out;
                if (appender.File.AppendTo == "true")
                {
                     mode += std::ios::app;
                }
                std::ofstream file(appender.File.Path, mode);
                file << log + "\n";
                file.close();
            }
        }
        else if (appender.Type == "ConsoleAppender") {
            if (appender.Enabled) {
                //TODO
                std::cout << log << std::endl;
            }
        }
        else if (appender.Type == "ColoredConsoleAppender") {
            if (appender.Enabled) {
                //TODO
            }
        }
    }
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

