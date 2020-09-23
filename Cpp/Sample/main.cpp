//---------------------------------------------------//
//                    MIT License                    //
// Copyright @ 2018-2020 Tony Su All Rights Reserved //
//        https://github.com/peitaosu/Logger         //
//---------------------------------------------------//

#include "Logger.h"

int main()
{
    Logger::Instance()->LoadConfig();
    Logger::Instance()->SetLogPath("New.log");
    Logger::Instance()->SetLogAppendTo(true);
    Logger::Instance()->EnableAppender("ConsoleAppender", false);
    Logger::Instance()->Information("Information");
    return 0;
}

