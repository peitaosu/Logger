#include "LogConfig.h"
#include "tinyxml2.h"

LogConfig::LogConfig(){
    LogConfig("LogConfig.xml");
}

LogConfig::LogConfig(std::string config) {
    this->config = config;
    tinyxml2::XMLDocument xml_doc;
    /* Get Current Working Directory

    #include <Windows.h>
    #include <direct.h>

    char buff[FILENAME_MAX];
    _getcwd(buff, FILENAME_MAX);
    std::string PWD(buff);
    std::string configFull = PWD + "\\" + this->config;
    */
    if (xml_doc.LoadFile(this->config.c_str()) != 0)
    {
        std::cout << "load xml file failed" << std::endl;
        return;
    }
    tinyxml2::XMLNode* root = xml_doc.FirstChild();
}

LogConfig::~LogConfig(){

}

std::list<LogAppender> LogConfig::GetLogAppenders()
{
    return this->_logAppenders;
}

LogRoot LogConfig::GetLogRoot()
{
    return this->_logRoot;
}
