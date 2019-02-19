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
    std::list<std::string> enabledAppender;
    for (auto& ref : this->_config.GetLogRoot().RootAppenderRefs)
    {
        enabledAppender.push_back(ref.Ref);
    }
    for (auto& appender : this->_config.GetLogAppenders()) {
        if (appender.Type == "FileAppender") {
            this->_fileAppenderEnabled = std::find(enabledAppender.begin(), enabledAppender.end(), appender.Name) != enabledAppender.end();
        }
        else if (appender.Type == "ConsoleAppender") {
            this->_consoleAppenderEnabled = std::find(enabledAppender.begin(), enabledAppender.end(), appender.Name) != enabledAppender.end();
        }
        else if (appender.Type == "ColoredConsoleAppender") {
            this->_coloredConsoleAppenderEnabled = std::find(enabledAppender.begin(), enabledAppender.end(), appender.Name) != enabledAppender.end();
        }
    }
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

