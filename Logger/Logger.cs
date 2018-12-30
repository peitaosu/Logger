using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Logger
{
    public class Logger : ILogger
    {
        public LogAppenderConfig FileLog = new LogAppenderConfig();
        public LogAppenderConfig ConsoleLog = new LogAppenderConfig();
        public LogAppenderConfig ColoredConsoleLog = new LogAppenderConfig();
        public LogRootConfig RootConfig = new LogRootConfig();

        private static Logger _logger = null;
        private static LogConfig _logConfig = null;
        private static readonly object syncObj = new object();
        private StreamWriter fileWriter;

        public Logger(){}

        public void LoadConfig(string config=null)
        {
            _logConfig = new LogConfig();
            if(config == null)
            {
                try
                {
                    _logConfig.Load(Path.Combine(Directory.GetCurrentDirectory(), "LogConfig.xml"));
                }
                catch (FileNotFoundException)
                {
                    _logConfig.Load(Path.Combine(Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location), "LogConfig.xml"));
                }
            }
            else
            {
                _logConfig.Load(config);
            }
            List<string> refedAppenders = new List<string>();
            foreach (LogConfig.RootAppenderRef appenderRef in _logConfig.Root.RootAppenderRefs)
            {
                refedAppenders.Add(appenderRef.Ref);
            }
            LogEventLevel minimumLevel = (LogEventLevel)Enum.Parse(typeof(LogEventLevel), _logConfig.Root.MinLevel.Value, true);
            RootConfig = new LogRootConfig { MinimumLevel = minimumLevel, RefedAppenders = refedAppenders };

            foreach (LogConfig.LogAppender appender in _logConfig.Appenders)
            {
                if (!RootConfig.RefedAppenders.Contains(appender.Name))
                {
                    continue;
                }
                switch (appender.Type)
                {
                    case "FileAppender":
                        FileLog = new LogAppenderConfig { IsEnabled = true, LogPath = appender.File.Path, LogAppendTo = (appender.File.AppendTo.Equals("true", StringComparison.OrdinalIgnoreCase)), LogPattern = appender.Pattern.Value, ColoredConsoleMapping = null };
                        if (!FileLog.LogAppendTo)
                        {
                            using (fileWriter = new StreamWriter(FileLog.LogPath, false)) { }
                        }
                        break;
                    case "ConsoleAppender":
                        ConsoleLog = new LogAppenderConfig { IsEnabled = true, LogPath = null, LogAppendTo = false, LogPattern = appender.Pattern.Value, ColoredConsoleMapping = null };
                        break;
                    case "ColoredConsoleAppender":
                        Dictionary<LogEventLevel, Dictionary<string, string>> levelColorMapping = new Dictionary<LogEventLevel, Dictionary<string, string>>();
                        foreach (LogConfig.AppenderColor color in appender.Colors)
                        {
                            Dictionary<string, string> colorMapping = new Dictionary<string, string>();
                            if (color.ForeColor != null) colorMapping.Add("ForeColor", color.ForeColor);
                            if (color.BackColor != null) colorMapping.Add("BackColor", color.BackColor);
                            levelColorMapping.Add((LogEventLevel)Enum.Parse(typeof(LogEventLevel), color.Level, true), colorMapping);
                        }
                        ColoredConsoleLog = new LogAppenderConfig { IsEnabled = true, LogPath = null, LogAppendTo = false, LogPattern = appender.Pattern.Value, ColoredConsoleMapping = levelColorMapping };
                        break;
                    default:
                        break;
                }
            }
        }

        public static Logger Instance
        {
            get
            {
                if (null == _logger)
                {
                    lock (syncObj)
                    {
                        if (null == _logger)
                        {
                            _logger = new Logger();
                            _logger.LoadConfig();
                        }
                    }
                }
                return _logger;
            }
        }

        public bool IsEnabled(LogEventLevel level)
        {
            if ((int)level < (int)RootConfig.MinimumLevel)
                return false;
            return true;
        }

        public void Write(LogEvent logEvent)
        {
            if (logEvent == null) return;
            if (!IsEnabled(logEvent.Level)) return;
            if (FileLog.IsEnabled)
            {
                using (fileWriter = new StreamWriter(FileLog.LogPath, true))
                {
                    fileWriter.WriteLine(FileLog.LogPattern, logEvent.Timestamp, logEvent.Level, logEvent.Message);
                    if (logEvent.Exception != null)
                    {
                        fileWriter.WriteLine(FileLog.LogPattern, logEvent.Timestamp, logEvent.Level, logEvent.Exception);
                    }
                }
            }
            if (ConsoleLog.IsEnabled)
            {
                Console.WriteLine(ConsoleLog.LogPattern, logEvent.Timestamp, logEvent.Level, logEvent.Message);
                if (logEvent.Exception != null)
                {
                    Console.WriteLine(ConsoleLog.LogPattern, logEvent.Timestamp, logEvent.Level, logEvent.Exception);
                }
            }
            if (ColoredConsoleLog.IsEnabled)
            {
                if (ColoredConsoleLog.ColoredConsoleMapping.ContainsKey(logEvent.Level))
                {
                    if (ColoredConsoleLog.ColoredConsoleMapping[logEvent.Level].ContainsKey("ForeColor"))
                    {
                        Console.ForegroundColor = (ConsoleColor)Enum.Parse(typeof(ConsoleColor), ColoredConsoleLog.ColoredConsoleMapping[logEvent.Level]["ForeColor"]);
                    }
                    if (ColoredConsoleLog.ColoredConsoleMapping[logEvent.Level].ContainsKey("BackColor"))
                    {
                        Console.BackgroundColor = (ConsoleColor)Enum.Parse(typeof(ConsoleColor), ColoredConsoleLog.ColoredConsoleMapping[logEvent.Level]["BackColor"]);
                    }
                }
                Console.WriteLine(ColoredConsoleLog.LogPattern, logEvent.Timestamp, logEvent.Level, logEvent.Message);
                if (logEvent.Exception != null)
                {
                    Console.WriteLine(ColoredConsoleLog.LogPattern, logEvent.Timestamp, logEvent.Level, logEvent.Exception);
                }
                Console.ResetColor();
            }
        }

        public void Write(LogEventLevel level, string message, Exception exception = null)
        {
            if (IsEnabled(level))
                Write(new LogEvent(DateTimeOffset.Now, level, message, exception));
        }

        public void Verbose(string message, Exception exception = null)
        {
            Write(LogEventLevel.Verbose, message, exception);
        }

        public void Debug(string message, Exception exception = null)
        {
#if DEBUG
            Write(LogEventLevel.Debug, message, exception);
#endif
        }

        public void Information(string message, Exception exception = null)
        {
            Write(LogEventLevel.Information, message, exception);
        }

        public void Warning(string message, Exception exception = null)
        {
            Write(LogEventLevel.Warning, message, exception);
        }

        public void Error(string message, Exception exception = null)
        {
            Write(LogEventLevel.Error, message, exception);
        }

        public void Fatal(string message, Exception exception = null)
        {
            Write(LogEventLevel.Fatal, message, exception);
        }
    }

    public class LogAppenderConfig
    {
        public bool IsEnabled = false;
        public string LogPath = null;
        public bool LogAppendTo = true;
        public string LogPattern = null;
        public Dictionary<LogEventLevel, Dictionary<string, string>> ColoredConsoleMapping = null;
    }

    public class LogRootConfig
    {
        public LogEventLevel MinimumLevel = LogEventLevel.Verbose;
        public List<string> RefedAppenders = null;
    }
}
