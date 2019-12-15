import os, sys
import lxml
from lxml import etree, objectify

def XMLValidate(xml_path, xsd_path):
    with open(xml_path) as in_file:
        in_xml = in_file.read()
    schema = etree.XMLSchema(file=xsd_path)
    parser = objectify.makeparser(schema=schema)
    try:
        objectify.fromstring(in_xml, parser)
    except etree.XMLSyntaxError as err:
        print(err.error_log)

if __name__=="__main__":
    XMLValidate(sys.argv[1], sys.argv[2])