//---------------------------------------------------//
//                    MIT License                    //
// Copyright @ 2018-2020 Tony Su All Rights Reserved //
//        https://github.com/peitaosu/Logger         //
//---------------------------------------------------//


#include "LogColor.h"

LogColor::LogColor()
{
}

LogColor::~LogColor()
{
}

void LogColor::UpdateColorMap(std::map<std::string, std::string> new_map)
{
    this->color_map = new_map;
}

std::string LogColor::GetColorByName(std::string name)
{
    if(this->color_map.find(name) != this->color_map.end())
        return this->color_map.find(name)->second;
    return return this->color_map..begin()->second;
}
