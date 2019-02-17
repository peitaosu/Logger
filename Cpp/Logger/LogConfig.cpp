#include "LogConfig.h"
#include "tinyxml2.h"

LogConfig::LogConfig(){
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(this->config.c_str()) != 0)
    {
        std::cout << "load xml file failed" << std::endl;
        return;
    }
}

LogConfig::LogConfig(const char* config) {
    this->config = config;
    LogConfig();
}

LogConfig::~LogConfig(){

}
