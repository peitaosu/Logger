using System;
using System.Collections.Generic;
using System.IO;
using System.Xml;
using System.Xml.Schema;

namespace Logging
{
    public class LogEvent
    {
        public LogEvent(DateTimeOffset timestamp, LogEventLevel level, string message)
        {
            Timestamp = timestamp;
            Level = level;
            Message = message;
        }

        public DateTimeOffset Timestamp { get; }
        public LogEventLevel Level { get; }
        public string Message { get; }
    }

    public enum LogEventLevel
    {
        VERBO,
        DEBUG,
        INFOR,
        WARNN,
        ERROR,
        FATAL
    }

    public class Logger
    {
        private static Logger _logger = null;
        private static readonly object _sync = new object();
        private StreamWriter _fileWriter;
        private static string _logPath = null;
        private static string _logPattern = "{0:yyyy/MM/dd H:mm:ss}: [{1}] {2}";
        
        public Logger(){}

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
                        }
                    }
                }
                return _logger;
            }
        }

        public void SetLogPath(string log)
        {
            this._logPath = log;
        }

        public void Write(LogEvent logEvent)
        {
            using (_fileWriter = new StreamWriter(this._logPath, true))
            {
                _fileWriter.WriteLine(this._logPattern, logEvent.Timestamp, logEvent.Level, logEvent.Message);
            }
            Console.WriteLine(this._logPattern, logEvent.Timestamp, logEvent.Level, logEvent.Message);
        }

        public void Write(LogEventLevel level, string message)
        {
            if (IsEnabled(level))
                Write(new LogEvent(DateTimeOffset.Now, level, message));
        }

        public void Verbose(string message)
        {
            Write(LogEventLevel.VERBO, message);
        }

        public void Debug(string message)
        {
            Write(LogEventLevel.DEBUG, message);
        }

        public void Information(string message)
        {
            Write(LogEventLevel.INFOR, message);
        }

        public void Warning(string message)
        {
            Write(LogEventLevel.WARNN, message);
        }

        public void Error(string message)
        {
            Write(LogEventLevel.ERROR, message);
        }

        public void Fatal(string message)
        {
            Write(LogEventLevel.FATAL, message);
        }
    }
}
