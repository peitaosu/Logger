// Logger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LogEvent.h"

int main()
{

    std::chrono::milliseconds time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    LogEventLevel level = LogEventLevel::INFOR;
    std::string log = "Hello World";
    LogEventException exception("NULL", "NULL");
    LogEvent event(time, level, log, exception);
    return 0;
}

