#include "LogEvent.h"

LogEventException::LogEventException() {
}

LogEventException::LogEventException(std::string summary)
{
    this->summary = summary;
}

LogEventException::LogEventException(std::string summary, std::string detail)
{
    this->summary = summary;
    this->detail = detail;
}

std::string LogEventException::GetSummary() {
    return this->summary;
}

std::string LogEventException::GetDetail() {
    return this->detail;
}


LogEvent::LogEvent() {
}

LogEvent::LogEvent(LogEventLevel level, std::string message) {
    auto time = std::time(nullptr);
    auto tm = *std::localtime(&time);
    this->timestamp = tm;
    this->level = level;
    this->message = message;
}

LogEvent::LogEvent(LogEventLevel level, std::string message, LogEventException exception) {
    auto time = std::time(nullptr);
    auto tm = *std::localtime(&time);
    this->timestamp = tm;
    this->level = level;
    this->message = message;
    this->exception = exception;
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

LogEventException LogEvent::GetException() {
    return this->exception;
}

