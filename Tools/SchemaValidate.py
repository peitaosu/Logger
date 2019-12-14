import os, sys
import lxml
from lxml import etree
from io import StringIO

def XMLValidate(xml_path, xsd_path):
    with open(xml_path) as in_file:
        in_xml = in_file.read()
    with open(xsd_path) as in_file:
        in_xsd = in_file.read()
    xsd_doc = etree.parse(StringIO(in_xsd))
    xsd = etree.XMLSchema(xsd_doc)
    try:
        doc = etree.parse(StringIO(in_xml))
    except etree.XMLSyntaxError as err:
        print(err.error_log)

if __name__=="__main__":
    XMLValidate(sys.argv[1], sys.argv[2])