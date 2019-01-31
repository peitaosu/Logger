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
            Logger.Logger.Instance.LoadConfig();
            Logger.Logger.Instance.FileLog.LogPath = "New.log";
            Logger.Logger.Instance.Information("Information");
            Logger.Logger.Instance.Debug("Debug");
            Logger.Logger.Instance.Error("Error");
            Console.Read();
        }
    }
}
