import xml.etree.ElementTree as ET

class LogConfig():
    def __init__(self, config):
        log_config = ET.parse(config).getroot()
        self.config = {
            "Appenders": {},
            "Root": {
                "MinLevel": "VERBO",
                "AppenderRef": []
            }
        }
        for child in log_config:
            if child.tag is "Appender":
                self.config["Appenders"][child.attrib["Name"]] = {}
                self.config["Appenders"][child.attrib["Name"]]["Type"] = child.attrib["Type"]
                self.config["Appenders"][child.attrib["Name"]]["File"] = {}
                self.config["Appenders"][child.attrib["Name"]]["Enabled"] = False
                self.config["Appenders"][child.attrib["Name"]]["Colors"] = {}
                for config in child:
                    if config.tag is "File":
                        self.config["Appenders"][child.attrib["Name"]]["File"]["Path"] = config.attrib["Path"]
                        self.config["Appenders"][child.attrib["Name"]]["File"]["AppendTo"] = config.attrib["AppendTo"]
                    if config.tag is "Pattern":
                        self.config["Appenders"][child.attrib["Name"]]["Pattern"] = config.attrib["Value"]
                    if config.tag is "Color":
                        self.config["Appenders"][child.attrib["Name"]]["Colors"][config.attrib["Level"]] = {
                            "ForeColor": config.attrib.get("ForeColor", None),
                            "BackColor": config.attrib.get("BackColor", None)
                        }
            if child.tag is "Root":
                for config in child:
                    if config.tag is "MinLevel":
                        self.config["Root"]["MinLevel"] = config.attrib["Value"]
                    if config.tag is "AppenderRef":
                        self.config["Root"]["AppenderRef"].append(config.attrib["Ref"])
                        self.config["Appenders"][child.attrib["Ref"]]["Enabled"] = True
    
    def UpdateLogAppenders(self, appenders):
        self.config["Appenders"] = appenders
    
    def GetLogAppenders(self):
        return self.config["Appenders"]
    
    def GetLogRoot(self):
        return self.config["Root"]
