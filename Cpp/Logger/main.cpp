// Logger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Logger.h"

int main()
{

    LogEventLevel level = LogEventLevel::INFOR;
    std::string log = "Hello World";
    LogEvent event(level, log);
    LogEventException exception;
    Logger::Instance()->Information("Hello", exception);
    return 0;
}

