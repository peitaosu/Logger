from Logger import Logger

logger = Logger()
logger.LoadConfig("LogConfig.xml")
logger.Information("Information")
logger.Debug("Debug")
logger.Error("Error")