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
        for appender in self._config.GetLogAppenders():
            if appender["Type"] == "FileAppender":
                self._logPath = appender["File"]["Path"]
                self._appendTo = appender["File"]["AppendTo"] == "True"

    def EnableAppender(self, appenderType, enable):
        for appender in self._config.GetLogAppenders():
            if appender["Type"] == appenderType:
                appender["Enabled"] = enable
    
    def SetLogPath(self, log):
        self._logPath = log
     
    def SetLogAppendTo(self, appendTo):
        if self._appendTo != appendTo:
            self._logFile = None
        self._appendTo = appendTo
    
    def IsEnabled(self, level):
        if level < self._minimalLevel.value:
            return False
        return True
    
    def Write(self, level, message, exception=None):
        if not self.IsEnabled(level):
            return
        for appender in self._config.GetLogAppenders():
            if appender["Enabled"]:
                if appender["Type"] == "FileAppender":
                    if not self._logFile:
                        if self._appendTo:
                            self._logFile = open(self._logPath, "a+")
                        else:
                            self._logFile = open(self._logPath, "w+")
                        self._logFile.write(appender["Pattern"].format(level, message, exception))
                if appender["Type"] == "ConsoleAppender":
                    print(appender["Pattern"].format(level, message, exception))
                if appender["Type"] == "ColoredConsoleAppender":
                    pass
    
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
