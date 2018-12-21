using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Logger
{
    class Program
    {
        static void Main(string[] args)
        {
            LogConfig logConfig = new LogConfig();
            logConfig.Load(Path.Combine(Directory.GetCurrentDirectory(), "LogConfig.xml"));
            Logger.Instance.LoadConfig(logConfig);
            Logger.Instance.Information("Information");
            Logger.Instance.Debug("Debug");
            Logger.Instance.Error("Error");
            Console.Read();
        }
    }
}
