﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Xml;
using System.Xml.Schema;

namespace Logging
{
    public class Logger
    {
        public LogAppenderConfig FileLog = new LogAppenderConfig();
        public LogAppenderConfig ConsoleLog = new LogAppenderConfig();
        public LogAppenderConfig ColoredConsoleLog = new LogAppenderConfig();
        public LogRootConfig RootConfig = new LogRootConfig();

        private static Logger _logger = null;
        private static LogConfig _logConfig = null;
        private static readonly object _sync = new object();
        private StreamWriter _fileWriter;
        private string _defaultConfig = "LogConfig.xml";
        private string _config = null;

        public Logger(){}

        public void LoadConfig(string config=null)
        {
            _logConfig = new LogConfig();
            if(config == null)
            {
                try
                {
                    _logConfig.Load(Path.Combine(Directory.GetCurrentDirectory(), _defaultConfig));
                }
                catch (FileNotFoundException)
                {
                    _logConfig.Load(Path.Combine(Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location), _defaultConfig));
                }
            }
            else
            {
                this._config = config;
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
                            using (_fileWriter = new StreamWriter(FileLog.LogPath, false)) { }
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
                    lock (_sync)
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

        public bool ValidateSchema(string xsdPath)
        {
            XmlDocument xml = new XmlDocument();
            xml.Load(this._config);
            xml.Schemas.Add(null, xsdPath);

            try
            {
                xml.Validate(null);
            }
            catch (XmlSchemaValidationException)
            {
                throw;
            }
            return true;
        }

        public void EnableAppender(string appenderType, bool enable = true)
        {
            switch (appenderType)
            {
                case "FileAppender":
                    FileLog.IsEnabled = enable;
                    break;
                case "ConsoleAppender":
                    ConsoleLog.IsEnabled = enable;
                    break;
                case "ColoredConsoleAppender":
                    ColoredConsoleLog.IsEnabled = enable;
                    break;
                default:
                    break;
            }
        }

        public void SetLogPath(string log)
        {
            this.FileLog.LogPath = log;
        }

        public void SetLogAppendTo(bool appendTo)
        {
            this.FileLog.LogAppendTo = appendTo;
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
                using (_fileWriter = new StreamWriter(FileLog.LogPath, true))
                {
                    _fileWriter.WriteLine(FileLog.LogPattern, logEvent.Timestamp, logEvent.Level, logEvent.Message);
                    if (logEvent.Exception != null)
                    {
                        _fileWriter.WriteLine(FileLog.LogPattern, logEvent.Timestamp, logEvent.Level, logEvent.Exception);
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
                Write(new LogEvent(level, message, exception));
        }

        public void Verbose(string message, Exception exception = null)
        {
            Write(LogEventLevel.VERBO, message, exception);
        }

        public void Debug(string message, Exception exception = null)
        {
#if DEBUG
            Write(LogEventLevel.DEBUG, message, exception);
#endif
        }

        public void Information(string message, Exception exception = null)
        {
            Write(LogEventLevel.INFOR, message, exception);
        }

        public void Warning(string message, Exception exception = null)
        {
            Write(LogEventLevel.WARNN, message, exception);
        }

        public void Error(string message, Exception exception = null)
        {
            Write(LogEventLevel.ERROR, message, exception);
        }

        public void Fatal(string message, Exception exception = null)
        {
            Write(LogEventLevel.FATAL, message, exception);
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
        public LogEventLevel MinimumLevel = LogEventLevel.VERBO;
        public List<string> RefedAppenders = null;
    }
}
