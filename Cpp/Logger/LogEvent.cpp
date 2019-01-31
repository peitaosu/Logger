#include "LogEvent.h"

LogEventException::LogEventException() {
};

LogEventException::LogEventException(std::string summary, std::string detail)
{
    this->summary = summary;
    this->detail = detail;
}

LogEvent::LogEvent() {
}

LogEvent::LogEvent(std::chrono::milliseconds timestamp, LogEventLevel level, std::string message, LogEventException exception) {
    this->timestamp = timestamp;
    this->level = level;
    this->message = message;
    this->exception = exception;
}
