import datetime
from enum import Enum

class LogEventLevel(Enum):
    VERBO = 0
    DEBUG = 1
    INFOR = 2
    WARNN = 3
    ERROR = 4
    FATAL = 5

class LogEvent():
    def __init__(self, level, message):
        self.message = message
        self.timestamp = datetime.datetime.now()
        self.level = level

    def GetTimestamp(self):
        return self.timestamp
    
    def GetLevel(self):
        return self.level

    def GetMessage(self):
        return self.message
    

class Logger():

    def __init__(self):
        self._minimalLevel = LogEventLevel.VERBO
        self._logPath = "Logger.log"
        self._appendTo = True
        self._logFile = None
    
    def SetLogPath(self, log):
        self._logPath = log
             
    def Write(self, level, message):
        self.WriteImp(LogEvent(level, message))
    
    def WriteImp(self, event):
        if not self._logFile:
            if self._appendTo:
                self._logFile = open(self._logPath, "a+")
            else:
                self._logFile = open(self._logPath, "w+")
        self._logFile.write(appender["Pattern"].format(event.GetTimestamp(), event.GetLevel().name, event.GetMessage()) + "\n")
        print(appender["Pattern"].format(event.GetTimestamp(), event.GetLevel().name, event.GetMessage()))

    def Verbose(self, message):
        self.Write(LogEventLevel.VERBO, message)

    def Debug(self, message):
        self.Write(LogEventLevel.DEBUG, message)

    def Information(self, message):
        self.Write(LogEventLevel.INFOR, message)

    def Warning(self, message):
        self.Write(LogEventLevel.WARNN, message)

    def Error(self, message):
        self.Write(LogEventLevel.ERROR, message)

    def Fatal(self, message):
        self.Write(LogEventLevel.FATAL, message)
