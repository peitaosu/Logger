using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Logger
{
    public interface ILogger
    {
        bool IsEnabled(LogEventLevel level);

        void Write(LogEvent logEvent);
        void Write(LogEventLevel level, string message);
        void Write(LogEventLevel level, string message, Exception exception);

        void Verbose(string message);
        void Verbose(string message, Exception exception);

        void Debug(string message);
        void Debug(string message, Exception exception);

        void Information(string message);
        void Information(string message, Exception exception);

        void Warning(string message);
        void Warning(string message, Exception exception);

        void Error(string message);
        void Error(string message, Exception exception);

        void Fatal(string message);
        void Fatal(string message, Exception exception);

    }
}
