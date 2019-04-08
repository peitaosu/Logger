from Logger import Logger

logger = Logger()
logger.LoadConfig("LogConfig.xml")
logger.SetLogPath("New.log")
logger.SetLogAppendTo(True)
logger.EnableAppender("ColoredConsoleAppender", True)
logger.Information("Information")
logger.Debug("Debug")
logger.Error("Error")