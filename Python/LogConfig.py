import xml.etree.ElementTree as ET

class LogConfig():
    def __init__(self, config):
        log_config = ET.parse(config).getroot()
        self.Appenders = {}
        self.Root = {
            "MinLevel": "VERBO",
            "AppenderRef": []
        }
        for child in log_config:
            if child.tag == r"{http://Logger/LogConfig.xsd}Appender":
                self.Appenders[child.attrib["Name"]] = {}
                self.Appenders[child.attrib["Name"]]["Type"] = child.attrib["Type"]
                self.Appenders[child.attrib["Name"]]["File"] = {}
                self.Appenders[child.attrib["Name"]]["Enabled"] = False
                self.Appenders[child.attrib["Name"]]["Colors"] = {}
                for config in child:
                    if config.tag == r"{http://Logger/LogConfig.xsd}File":
                        self.Appenders[child.attrib["Name"]]["File"]["Path"] = config.attrib["Path"]
                        self.Appenders[child.attrib["Name"]]["File"]["AppendTo"] = config.attrib["AppendTo"]
                    if config.tag == r"{http://Logger/LogConfig.xsd}Pattern":
                        self.Appenders[child.attrib["Name"]]["Pattern"] = config.attrib["Value"]
                    if config.tag == r"{http://Logger/LogConfig.xsd}Color":
                        self.Appenders[child.attrib["Name"]]["Colors"][config.attrib["Level"]] = {
                            "ForeColor": config.attrib.get("ForeColor", None),
                            "BackColor": config.attrib.get("BackColor", None)
                        }
            if child.tag == r"{http://Logger/LogConfig.xsd}Root":
                for config in child:
                    if config.tag == r"{http://Logger/LogConfig.xsd}MinLevel":
                        self.Root["MinLevel"] = config.attrib["Value"]
                    if config.tag == r"{http://Logger/LogConfig.xsd}AppenderRef":
                        self.Root["AppenderRef"].append(config.attrib["Ref"])
                        self.Appenders[config.attrib["Ref"]]["Enabled"] = True
    
    def UpdateLogAppenders(self, appenders):
        self.Appenders = appenders
    
    def GetLogAppenders(self):
        return self.Appenders
    
    def GetLogRoot(self):
        return self.Root
