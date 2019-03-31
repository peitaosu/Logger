class AppenderFile():
    def __init__(self, Path, AppendTo):
        self.Path = Path
        self.AppendTo = AppendTo

class AppenderPattern():
    def __init__(self, Value):
        self.Value = Value

class AppenderColor():
    def __init__(self, Level, ForeColor, BackColor):
        self.Level = Level
        self.ForeColor = ForeColor
        self.BackColor = BackColor

class LogAppender():
    def __init__(self, Enabled, Name, Type, File, Pattern, Colors):
        self.Enabled = Enabled
        self.Name = Name
        self.Type = Type
        self.File = File
        self.Pattern = Pattern
        self.Colors = Colors

class RootMinLevel():
    def __init__(self, Value):
        self.Value = Value


class RootAppenderRef():
    def __init__(self, Ref):
        self.Ref = Ref

class LogRoot():
    def __init__(self, MinLevel, RootAppenderRefs):
        self.MinLevel = MinLevel
        self.RootAppenderRefs = RootAppenderRefs

class LogConfig():
    def __init__(self):
        self.config = None
        self._logAppenders = []
        self._logRoot = None
    
    def UpdateLogAppenders(self, appenders):
        self._logAppenders = appenders
    
    def GetLogAppenders(self):
        return self._logAppenders
    
    def GetLogRoot(self):
        return self._logRoot
