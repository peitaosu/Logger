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
    tinyxml2::XMLNode* root = xml_doc.FirstChildElement("Logger");
    for (tinyxml2::XMLElement* element = root->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
    {
        if (strcmp(element->Name(), "Appender") == 0) {
            LogAppender appender;
            appender.Enabled = false;
            appender.Name = element->Attribute("Name");
            appender.Type = element->Attribute("Type");
            for (tinyxml2::XMLElement* appenderElement = element->FirstChildElement(); appenderElement != NULL; appenderElement = appenderElement->NextSiblingElement()) {
                if (strcmp(appenderElement->Name(), "File") == 0) {
                    appender.File = { appenderElement->Attribute("Path"), appenderElement->Attribute("AppendTo") };
                }else if (strcmp(appenderElement->Name(), "Pattern") == 0) {
                    appender.Pattern = { appenderElement->Attribute("Value") };
                }else if (strcmp(appenderElement->Name(), "Color") == 0) {
                    AppenderColor color;
                    color.Level = appenderElement->Attribute("Level");
                    if (appenderElement->Attribute("ForeColor")) color.ForeColor = appenderElement->Attribute("ForeColor");
                    if (appenderElement->Attribute("BackColor")) color.ForeColor = appenderElement->Attribute("BackColor");
                    appender.Colors.push_back(color);
                }
            }
            this->_logAppenders.push_back(appender);
        }
        else if(strcmp(element->Name(), "Root") == 0){
            for (tinyxml2::XMLElement* rootElement = element->FirstChildElement(); rootElement != NULL; rootElement = rootElement->NextSiblingElement()) {
                if (strcmp(rootElement->Name(), "MinLevel") == 0) {
                    this->_logRoot.MinLevel = { rootElement->Attribute("Value") };
                }else if (strcmp(rootElement->Name(), "AppenderRef") == 0) {
                    this->_logRoot.RootAppenderRefs.push_back({ rootElement->Attribute("Ref") });
                }
            }
        }
    }
    for (auto& appender : this->_logAppenders) {
        for (auto& ref : this->_logRoot.RootAppenderRefs) {
            if (appender.Name.compare(ref.Ref) == 0) {
                appender.Enabled = true;
            }
        }
    }
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
