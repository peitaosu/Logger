using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Logger
{
    public class LogEvent
    {
        public LogEvent(DateTimeOffset timestamp, LogEventLevel level, string message, Exception exception = null)
        {
            Timestamp = timestamp;
            Level = level;
            Message = message;
            Exception = exception;
        }

        public DateTimeOffset Timestamp { get; }
        public LogEventLevel Level { get; }
        public string Message { get; }
        public Exception Exception { get; }
    }

    public enum LogEventLevel
    {
        Verbose,
        Debug,
        Information,
        Warning,
        Error,
        Fatal
    }

}
