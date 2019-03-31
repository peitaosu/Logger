import datetime
from enum import Enum

class LogEventLevel(Enum):
    VERBO = 0
    DEBUG = 1
    INFOR = 2
    WARNN = 3
    ERROR = 4
    FATAL = 5

class LogEventException():
    def __init__(self, summary,  detail=None):
        self.summary = summary
        self.detail = detail

    def GetSummary(self):
        return self.summary
    
    def GetDetail(self):
        return self.detail

class LogEvent():
    def __init__(self, level, message, exception=None):
        self.message = message
        self.exception = exception
        self.timestamp = datetime.datetime.now()
        self.level = level

    def GetTimestamp(self):
        return self.timestamp
    
    def GetLevel(self):
        return self.level

    def GetMessage(self):
        return self.message
    
    def GetException(self):
        return self.exception

