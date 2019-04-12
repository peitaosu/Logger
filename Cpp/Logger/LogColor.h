//---------------------------------------------------//
//                    MIT License                    //
// Copyright @ 2018-2019 Tony Su All Rights Reserved //
//        https://github.com/peitaosu/Logger         //
//---------------------------------------------------//

#include <iostream>
#include <map>

namespace Logging {
    class LogColor;
}

class LogColor {
public:
    LogColor();
    ~LogColor();
    void UpdateColorMap(std::map<std::string, std::string>);
    std::string GetColorByName(std::string name);
    
private:
    std::map<std::string, std::string> color_map = {
        {"PURPLE" , "\033[95m"},
        {"BLUE" , "\033[94m"},
        {"GREEN" , "\033[92m"},
        {"YELLOW" , "\033[93m"},
        {"RED" , "\033[91m"},
        {"ENDC" , "\033[0m"}
    };
};



