#include "stdafx.h"
#include "Logger.h"
#include <string>
#include <Windows.h>

int main()
{
    Logger::Instance()->LoadConfig();
    Logger::Instance()->Information("Information");
    return 0;
}

