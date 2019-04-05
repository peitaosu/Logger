from LogEvent import *
from LogConfig import *

class Logger():

    def __init__(self):
        self._minimalLevel = LogEventLevel.VERBO
        self._config = None
        self._defaultConfig = "LogConfig.xml"
        self._logPath = "Logger.log"
        self._appendTo = True
        self._logFile = None
    
    def LoadConfig(self, config=None):
        if not config:
            config = self._defaultConfig
        self._config = LogConfig(config)
        self._minimalLevel = LogEventLevel[self._config.GetLogRoot()["MinLevel"]]
        for appender_name in self._config.GetLogAppenders():
            if self._config.GetLogAppenders()[appender_name]["Type"] == "FileAppender":
                self._logPath = self._config.GetLogAppenders()[appender_name]["File"]["Path"]
                self._appendTo = self._config.GetLogAppenders()[appender_name]["File"]["AppendTo"] == "True"

    def EnableAppender(self, appenderType, enable):
        for appender_name in self._config.GetLogAppenders():
            if self._config.GetLogAppenders()[appender_name]["Type"] == appenderType:
                self._config.GetLogAppenders()[appender_name]["Enabled"] = enable
    
    def SetLogPath(self, log):
        self._logPath = log
     
    def SetLogAppendTo(self, appendTo):
        if self._appendTo != appendTo:
            self._logFile = None
        self._appendTo = appendTo
    
    def IsEnabled(self, level):
        if level.value < self._minimalLevel.value:
            return False
        return True
    
    def Write(self, level, message, exception=None):
        self.WriteImp(LogEvent(level, message, exception))
    
    def WriteImp(self, event):
        if not self.IsEnabled(event.GetLevel()):
            return
        for appender_name in self._config.GetLogAppenders():
            appender = self._config.GetLogAppenders()[appender_name]
            if appender["Enabled"]:
                if appender["Type"] == "FileAppender":
                    if not self._logFile:
                        if self._appendTo:
                            self._logFile = open(self._logPath, "a+")
                        else:
                            self._logFile = open(self._logPath, "w+")
                    self._logFile.write(appender["Pattern"].format(event.GetTimestamp(), event.GetLevel().name, event.GetMessage()) + "\n")
                if appender["Type"] == "ConsoleAppender":
                    print(appender["Pattern"].format(event.GetTimestamp(), event.GetLevel().name, event.GetMessage()))
                if appender["Type"] == "ColoredConsoleAppender":
                    print(appender["Pattern"].format(event.GetTimestamp(), event.GetLevel().name, event.GetMessage()))
    
    def Verbose(self, message, exception=None):
        self.Write(LogEventLevel.VERBO, message, exception)

    def Debug(self, message, exception=None):
        self.Write(LogEventLevel.DEBUG, message, exception)

    def Information(self, message, exception=None):
        self.Write(LogEventLevel.INFOR, message, exception)

    def Warning(self, message, exception=None):
        self.Write(LogEventLevel.WARNN, message, exception)

    def Error(self, message, exception=None):
        self.Write(LogEventLevel.ERROR, message, exception)

    def Fatal(self, message, exception=None):
        self.Write(LogEventLevel.FATAL, message, exception)
