# Simple Logger
[![GitHub license](https://img.shields.io/github/license/peitaosu/Logger.svg)](https://github.com/peitaosu/Logger/blob/master/LICENSE)

Simple implementation of Logger.

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
<Appender Name="ColoredConsoleAppender" Type="ColoredConsoleAppender">
    <Color Level="Error" ForeColor="Red"/>
    <Color Level="Debug" ForeColor="Green"/>
    <Color Level="Information" ForeColor="White"/>
    <Pattern Value="{0:yyyy/MM/dd H:mm:ss}: [{1}] {2}"/>
</Appender>
<Root>
    <MinLevel Value="Verbose" />
    <AppenderRef Ref="ColoredConsoleAppender" />
    <AppenderRef Ref="FileAppender" />
</Root>
```

## Example Code

```
Logger.Instance.LoadConfig();
// or load config with specific file
// Logger.Instance.LoadConfig("LogConfig.xml");
Logger.Instance.FileLog.LogPath = "New.log";
Logger.Instance.Information("Information");
Logger.Instance.Debug("Debug");
Logger.Instance.Error("Error");
```


