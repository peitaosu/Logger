#include "stdafx.h"
#include "Logger.h"

int main()
{
    Logger::Instance()->LoadConfig();
    Logger::Instance()->Information("Information");
    return 0;
}

