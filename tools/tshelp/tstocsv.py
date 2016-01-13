#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import sys
import xml.etree.ElementTree as ET
import csv
from utils import *

if len(sys.argv) < 4:
    print("Usage: python3 tstocsv.py in_zh_ts in_en_ts out_file")
    exit
print(sys.argv[1])
inZhTSContexts = ET.parse(sys.argv[1]).getroot().findall("context");
inEnTsContexts = ET.parse(sys.argv[2]).getroot().findall("context");

#print(len(inZhTSMessages))



zhNameToContextMap = buildData(inZhTSContexts)
enNameToContextMap = buildData(inEnTsContexts)

toWrite = ""
for ct in zhNameToContextMap:
    zhMessages = zhNameToContextMap[ct]
    enMessages = {}

    if ct not in enNameToContextMap:
         for source in zhMessages:
             m = zhMessages[source]
             enMessages[source] = {"source":m["source"], "tr":m["source"]}
    else:
        enMessages = enNameToContextMap[ct]
    for source in zhMessages:
        zhMessage = zhMessages[source]
        enMessage = enMessages[source]
        enTr = enMessage["tr"]
        zhTr = zhMessage["tr"]
        toWriteSource = '"' + zhMessage["source"] + '"'
        if enTr == None:
            toWriteEnTr = toWriteSource
        else:
            toWriteEnTr = '"' + enMessage["tr"] + '"'
        if zhTr == None:
            toWriteZhTr = toWriteSource
        else:
            toWriteZhTr = '"' + zhMessage["tr"] + '"'

        toWriteCt = '"' + ct + '"'
        toWrite += toWriteCt + "," + toWriteSource + "," + toWriteZhTr + "," + toWriteEnTr + "\n"
        #print(toWriteCt, toWriteSource, toWriteZhTr, toWriteEnTr)

print(toWrite)
outputFile = open(sys.argv[3], 'w')
outputFile.write(toWrite)
outputFile.close()
