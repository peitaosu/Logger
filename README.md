# Simple Logger
[![GitHub license](https://img.shields.io/github/license/peitaosu/Logger.svg)](https://github.com/peitaosu/Logger/blob/master/LICENSE)

Simple implementation of Logger. Now there are several languages implementations: C#, C++ and Python.

## LogConfig.xml

Customize your logger behavior by changing source code or only changing the `LogConfig.xml` for example log pattern, console colors, etc.

```
<Appender Name="FileAppender" Type="FileAppender">
    <File Path="Logger.log" AppendTo="true"/>
    <Pattern Value="{0:yyyy/MM/dd H:mm:ss}: [{1}] {2}"/>
</Appender>
<Appender Name="ConsoleAppender" Type="ConsoleAppender">
    <Pattern Value="{0:yyyy/MM/dd H:mm:ss}: [{1}] {2}"/>
</Appender>
<!-- ColoredConsoleAppender only available in C# -->
<Appender Name="ColoredConsoleAppender" Type="ColoredConsoleAppender">
    <Color Level="ERROR" ForeColor="Red"/>
    <Color Level="DEBUG" ForeColor="Green"/>
    <Color Level="INFOR" ForeColor="White"/>
    <Pattern Value="{0:yyyy/MM/dd H:mm:ss}: [{1}] {2}"/>
</Appender>
<Root>
    <MinLevel Value="VERBO" />
    <AppenderRef Ref="ColoredConsoleAppender" />
    <AppenderRef Ref="FileAppender" />
</Root>
```

## Example Code (C#)

```
Logging.Instance.LoadConfig();
// or load config with specific file
// Logging.Instance.LoadConfig("LogConfig.xml");
Logging.Logger.Instance.SetLogPath("New.log");
Logging.Logger.Instance.SetLogAppendTo(true);
// change the enable status of appender
Logging.Logger.Instance.EnableAppender("ColoredConsoleAppender", false);
Logging.Logger.Instance.Information("Information");
Logging.Logger.Instance.Debug("Debug");
Logging.Logger.Instance.Error("Error");
```


## Example Code (C++)

```
Logger::Instance()->LoadConfig();
Logger::Instance()->SetLogPath("New.log");
Logger::Instance()->SetLogAppendTo(true);
// change the enable status of appender
Logger::Instance()->EnableAppender("ConsoleAppender", false);
Logger::Instance()->Information("Information");
```


## Example Code (Python)

```
from Logger import Logger

logger = Logger()
logger.LoadConfig("LogConfig.xml")
logger.SetLogPath("New.log")
logger.SetLogAppendTo(True)
logger.EnableAppender("ColoredConsoleAppender", True)
logger.Information("Information")
logger.Debug("Debug")
logger.Error("Error")
```

## Tools
* SchemaValidate.py

## Simple
* /Simple
