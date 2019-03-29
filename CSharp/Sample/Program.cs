using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sample
{
    class Program
    {
        static void Main(string[] args)
        {
            Logging.Logger.Instance.LoadConfig();
            Logging.Logger.Instance.SetLogPath("New.log");
            Logging.Logger.Instance.SetLogAppendTo(true);
            Logging.Logger.Instance.EnableAppender("ColoredConsoleAppender", true);
            Logging.Logger.Instance.Information("Information");
            Logging.Logger.Instance.Debug("Debug");
            Logging.Logger.Instance.Error("Error");
            Console.Read();
        }
    }
}
