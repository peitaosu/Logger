//---------------------------------------------------//
//                    MIT License                    //
// Copyright @ 2018-2019 Tony Su All Rights Reserved //
//        https://github.com/peitaosu/Logger         //
//---------------------------------------------------//

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
    for (auto& appender : this->_config.GetLogAppenders()) {
        if (appender.Type == "FileAppender" && appender.Enabled) {
            this->_logPath = appender.File.Path;
            if (appender.File.AppendTo == "false") {
                this->_appendTo = false;
            }
        }
    }
}

void Logger::EnableAppender(std::string appenderType) {
    EnableAppender(appenderType, true);
}

void Logger::EnableAppender(std::string appenderType, bool enable) {
    std::list<LogAppender> appenders = this->_config.GetLogAppenders();
    for (auto& appender : appenders) {
        if (appender.Type.compare(appenderType) == 0) {
            appender.Enabled = enable;
        }
    }
    this->_config.UpdateLogAppenders(appenders);
}

void Logger::SetLogPath(std::string log) {
    this->_logPath = log;
}

void Logger::SetLogAppendTo(bool appendTo)
{
    this->_appendTo = appendTo;
}

bool Logger::IsEnabled(LogEventLevel level) {
    if(level < this->_minimalLevel) return false;
    return true;
}

void Logger::Write(LogEvent logEvent) {
    for (auto& appender : this->_config.GetLogAppenders()) {
        if (!appender.Enabled) continue;
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
        }
        std::string fmt = appender.Pattern.Value;
        std::string time_fmt, level_fmt, log_fmt, whole_fmt;
        std::regex pieces_regex(".*\\{(.*?)\\}.*\\{(.*?)\\}.*\\{(.*?)\\}.*");
        std::smatch pieces_match;
        if (std::regex_match(fmt, pieces_match, pieces_regex)) {
            time_fmt = pieces_match[1].str();
            if (time_fmt == "0") time_fmt = "%Y/%m/%d %H:%M:%S";
            level_fmt = pieces_match[2].str();
            if (level_fmt == "1") level_fmt = "%s";
            log_fmt = pieces_match[3].str();
            if (log_fmt == "2") log_fmt = "%s";
            std::ostringstream time_string;
            time_string << std::put_time(&logEvent.GetTimestamp(), time_fmt.c_str());
            log = fmt;
            size_t index = 0;
            index = log.find("{" + pieces_match[1].str() + "}", index);
            log.replace(index, pieces_match[1].str().size() + 2, time_string.str());
            index = log.find("{" + pieces_match[2].str() + "}", index);
            log.replace(index, pieces_match[2].str().size() + 2, level);
            index = log.find("{" + pieces_match[3].str() + "}", index);
            log.replace(index, pieces_match[3].str().size() + 2, logEvent.GetMessage());
        }
        else
        {
            std::ostringstream time_string;
            time_string << std::put_time(&logEvent.GetTimestamp(), "%Y/%m/%d %H:%M:%S");
            log = time_string.str() + ": [" + level + "] " + logEvent.GetMessage();
        }
        if (logEvent.GetException().GetSummary() != "") {
            log = log + "\n";
            log += logEvent.GetException().GetSummary();
        }
        if (appender.Type == "FileAppender") {
            int mode = std::ios::out;
            if (this->_appendTo)
            {
                    mode += std::ios::app;
            }
            std::ofstream file(this->_logPath, mode);
            file << log + "\n";
            file.close();
        }
        else if (appender.Type == "ConsoleAppender") {
            std::cout << log << std::endl;
        }
        else if (appender.Type == "ColoredConsoleAppender") {
            bool color_not_found = true;
            for (auto& color : appender.Colors) {
                if (color.Level == level && color.ForeColor != "") {
                    std::cout << this->_logColor.GetColorByName(color.ForeColor) << log << this->_logColor.GetColorByName("ENDC") << std::endl;
                    color_not_found = false;
                }
            }
            if(color_not_found) std::cout << log << std::endl;
        }
    }
}

void Logger::Write(LogEventLevel level, std::string message) {
    LogEventException exception;
    if (IsEnabled(level))
        Write(LogEvent(level, message, exception));
}

void Logger::Write(LogEventLevel level, std::string message, LogEventException exception) {
    if (IsEnabled(level))
        Write(LogEvent(level, message, exception));
}

void Logger::Verbose(std::string message) {
    Write(LogEventLevel::VERBO, message);
}

void Logger::Verbose(std::string message, LogEventException exception) {
    Write(LogEventLevel::VERBO, message, exception);
}

void Logger::Debug(std::string message) {
    Write(LogEventLevel::DEBUG, message);
}

void Logger::Debug(std::string message, LogEventException exception) {
    Write(LogEventLevel::DEBUG, message, exception);
}

void Logger::Information(std::string message) {
    Write(LogEventLevel::INFOR, message);
}

void Logger::Information(std::string message, LogEventException exception) {
    Write(LogEventLevel::INFOR, message, exception);
}

void Logger::Warning(std::string message) {
    Write(LogEventLevel::WARNN, message);
}

void Logger::Warning(std::string message, LogEventException exception) {
    Write(LogEventLevel::WARNN, message, exception);
}

void Logger::Error(std::string message) {
    Write(LogEventLevel::ERROR, message);
}

void Logger::Error(std::string message, LogEventException exception) {
    Write(LogEventLevel::ERROR, message, exception);
}

void Logger::Fatal(std::string message) {
    Write(LogEventLevel::FATAL, message);
}

void Logger::Fatal(std::string message, LogEventException exception) {
    Write(LogEventLevel::FATAL, message, exception);
}

Logger* Logger::_logger = nullptr;

