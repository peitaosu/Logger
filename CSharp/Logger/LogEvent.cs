using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Logging
{
    public class LogEvent
    {
        public LogEvent(LogEventLevel level, string message, Exception exception = null)
        {
            Timestamp = DateTimeOffset.Now;
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
        VERBO,
        DEBUG,
        INFOR,
        WARNN,
        ERROR,
        FATAL
    }

}
