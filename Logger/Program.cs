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
            Logger.Instance.LoadConfig();
            Logger.Instance.Information("Information");
            Logger.Instance.Debug("Debug");
            Logger.Instance.Error("Error");
            Console.Read();
        }
    }
}
