#include "stdafx.h"
#include "Logger.h"

int main()
{
    Logger::Instance()->LoadConfig();
    Logger::Instance()->SetLogPath("New.log");
    Logger::Instance()->Information("Information");
    return 0;
}

