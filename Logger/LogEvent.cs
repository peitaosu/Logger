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
        public LogEvent(DateTimeOffset timestamp, LogEventLevel level, Exception exception)
        {
            Timestamp = timestamp;
            Level = level;
            Exception = exception;
        }

        public DateTimeOffset Timestamp { get; }
        public LogEventLevel Level { get; }
        public Exception Exception { get; }

        public string RenderMessage(IFormatProvider formatProvider = null)
        {
            var writer = new StringWriter(formatProvider);
            return writer.ToString();
        }
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
