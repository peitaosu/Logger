
#include <iostream>
#include <list>

namespace Logging {
    class LogConfig;
    struct LogAppender;
    struct AppenderFile;
    struct AppenderPattern;
    struct AppenderColor;
    struct LogRoot;
    struct RootMinLevel;
    struct RootAppenderRef;
}

struct AppenderFile
{
    std::string Path;
    std::string AppendTo;
};

struct AppenderPattern
{
    std::string Value;
};

struct AppenderColor
{
    std::string Level;
    std::string ForeColor;
    std::string BackColor;
};

struct LogAppender
{
    std::string Name;
    std::string Type;
    AppenderFile File;
    AppenderPattern Pattern;
    std::list<AppenderColor> Colors;
};

struct RootMinLevel
{
    std::string Value;
};

struct RootAppenderRef
{
    std::string Ref;
};

struct LogRoot
{
    RootMinLevel MinLevel;
    std::list<RootAppenderRef> RootAppenderRefs;
};

class LogConfig {
public:
    LogConfig();
    LogConfig(const char* config);
    ~LogConfig();
    std::list<LogAppender> GetLogAppenders();
    LogRoot GetLogRoot();
private:
    std::string config = "LogConfig.xml";
    std::list<LogAppender> _logAppenders;
    LogRoot _logRoot;
};




