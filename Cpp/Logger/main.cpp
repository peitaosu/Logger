//---------------------------------------------------//
//                    MIT License                    //
// Copyright @ 2018-2019 Tony Su All Rights Reserved //
//        https://github.com/peitaosu/Logger         //
//---------------------------------------------------//

#include "stdafx.h"
#include "Logger.h"

int main()
{
    Logger::Instance()->LoadConfig();
    Logger::Instance()->SetLogPath("New.log");
    Logger::Instance()->Information("Information");
    return 0;
}

