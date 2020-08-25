#include "LogEvent.h"

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
