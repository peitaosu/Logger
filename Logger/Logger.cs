using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Logger
{
    public class Logger : ILogger
    {
        readonly LogEventLevel _minimumLevel;
        readonly Action _dispose;

        Logger(
            LogEventLevel minimumLevel,
            Action dispose = null)
        {
            _minimumLevel = minimumLevel;
            _dispose = dispose;
        }

        public bool IsEnabled(LogEventLevel level)
        {
            if ((int)level < (int)_minimumLevel)
                return false;
            return true;
        }

        public void Write(LogEvent logEvent)
        {
            if (logEvent == null) return;
            if (!IsEnabled(logEvent.Level)) return;
            Dispatch(logEvent);
        }

        public void Write(LogEventLevel level, string message)
        {
            if (IsEnabled(level))
                Write(level, message);
        }

        public void Write(LogEventLevel level, string message, Exception exception)
        {
            if (IsEnabled(level))
                Write(level, message, exception);
        }

        void Dispatch(LogEvent logEvent)
        {
            //TODO
        }

        public void Verbose(string message)
        {
            Write(LogEventLevel.Verbose, message);
        }

        public void Verbose(string message, Exception exception)
        {
            Write(LogEventLevel.Verbose, message, exception);
        }

        public void Debug(string message)
        {
            Write(LogEventLevel.Debug, message);
        }

        public void Debug(string message, Exception exception)
        {
            Write(LogEventLevel.Debug, message, exception);
        }

        public void Information(string message)
        {
            Write(LogEventLevel.Information, message);
        }

        public void Information(string message, Exception exception)
        {
            Write(LogEventLevel.Information, message, exception);
        }

        public void Warning(string message)
        {
            Write(LogEventLevel.Warning, message);
        }

        public void Warning(string message, Exception exception)
        {
            Write(LogEventLevel.Warning, message, exception);
        }

        public void Error(string message)
        {
            Write(LogEventLevel.Error, message);
        }

        public void Error(string message, Exception exception)
        {
            Write(LogEventLevel.Error, message, exception);
        }

        public void Fatal(string message)
        {
            Write(LogEventLevel.Fatal, message);
        }

        public void Fatal(string message, Exception exception)
        {
            Write(LogEventLevel.Fatal, message, exception);
        }
    }
}
