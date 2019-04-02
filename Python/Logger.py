from LogEvent import *
from LogConfig import *

class Logger():

    def __init__(self):
        self._minimalLevel = LogEventLevel.VERBO
        self._config = None
        self._defaultConfig = "LogConfig.xml"
        self._logPath = "Logger.log"
        self._appendTo = True
    
    def LoadConfig(self, config=None):
        if not config:
            config = self._defaultConfig
        self._config = LogConfig(config)
        self._minimalLevel = LogEventLevel[self._config.GetLogRoot()["MinLevel"]]

    def EnableAppender(self, appenderType, enable):
        for appender in self._config.GetLogAppenders():
            if appender["Type"] == appenderType:
                appender["Enabled"] = enable
    
    def SetLogPath(self, log):
        pass
    
    def SetLogAppendTo(self, appendTo):
        pass
    
    def IsEnabled(self, level):
        if level < self._minimalLevel.value:
            return False
        return True
    
    def Write(self, level, message, exception=None):
        if not self.IsEnabled(level):
            return
        # TODO: File Log
        # TODO: Console Log
        # TODO: Colored Console Log
    
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
