using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace Logger
{
    [XmlRoot(ElementName = "Logger", Namespace = "http://schemas.microsoft.com/wix/2006/wi")]
    public class LogConfig
    {
        [XmlElement("Appender")]
        public List<LogAppender> Appenders;
        [XmlElement("Root")]
        public LogRoot Root;

        public LogConfig()
        {
            Appenders = new List<LogAppender>();
        }

        public struct LogAppender
        {
            [XmlAttribute]
            public string Name;
            [XmlAttribute]
            public string Type;
            [XmlElement("File")]
            public AppenderFile File;
            [XmlElement("AppendToFile")]
            public AppenderAppendToFile AppendToFile;
            [XmlElement("Pattern")]
            public AppenderPattern Pattern;
            [XmlElement("Color")]
            public List<AppenderColor> Colors;
        }

        public struct AppenderFile
        {
            [XmlAttribute]
            public string Value;
        }
        public struct AppenderAppendToFile
        {
            [XmlAttribute]
            public string Value;
        }
        public struct AppenderPattern
        {
            [XmlAttribute]
            public string Value;
        }

        public struct AppenderColor
        {
            [XmlAttribute]
            public string Level;
            [XmlAttribute]
            public string ForeColor;
            [XmlAttribute]
            public string BackColor;
        }

        public struct LogRoot
        {
            [XmlElement("MinLevel")]
            public RootMinLevel MinLevel;
            [XmlElement("AppenderRef")]
            public List<RootAppenderRef> RootAppenderRefs;
        }

        public struct RootMinLevel
        {
            [XmlAttribute]
            public string Value;
        }
        public struct RootAppenderRef
        {
            [XmlAttribute]
            public string Ref;
        }

        public void Load(string filePath)
        {
            XmlSerializer serializer = new XmlSerializer(GetType());
            LogConfig obj = Deserialize(serializer, filePath);
            if (null == obj || !CopyFrom(obj))
                Debug.Assert(false, "Failed to load data from XML: " + filePath);
        }

        public LogConfig Deserialize(XmlSerializer serializer, string filePath)
        {
            LogConfig obj = null;
            try
            {
                using (var stream = new FileStream(filePath, FileMode.Open, FileAccess.Read))
                {
                    obj = (LogConfig)serializer.Deserialize(stream);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("Error opening file: {0}", filePath);
                Console.WriteLine(e.Message);
            }
            return obj;
        }

        public bool CopyFrom(LogConfig obj)
        {
            LogConfig source = obj as LogConfig;
            if (null == source) return false;
            if (null != source.Appenders)
                Appenders = source.Appenders;
            if (!source.Root.Equals(default(LogRoot)))
                Root = source.Root;
            return true;
        }
    }

}
