#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import sys
import xml.etree.ElementTree as ET
import csv
import json
from utils import *

if len(sys.argv) < 4:
    print("Usage: python3 tstocsv.py in_zh_ts in_en_ts out_file langconfig")
    exit
print(sys.argv[1])
inZhTSContexts = ET.parse(sys.argv[1]).getroot().findall("context");
inEnTsContexts = ET.parse(sys.argv[2]).getroot().findall("context");

#print(len(inZhTSMessages))
langconfig = json.loads(open(sys.argv[4], 'r').read());

zhNameToContextMap = buildData(inZhTSContexts)
enNameToContextMap = buildData(inEnTsContexts)
lgCMs = {}
for lg in langconfig:
    lgCMs[lg] = buildData(ET.parse(langconfig[lg]).getroot().findall("context"));


toWrite = ""
for ct in zhNameToContextMap:
    zhMessages = zhNameToContextMap[ct]
    enMessages = {}
    lgMessagesMap = {}

    if ct not in enNameToContextMap:
         for source in zhMessages:
             m = zhMessages[source]
             enMessages[source] = {"source":m["source"], "tr":m["source"]}
    else:
        enMessages = enNameToContextMap[ct]
        
    for lg in lgCMs:
        if ct not in lgCMs[lg]:
            for source in zhMessages:
                m = zhMessages[source]
                if lg not in lgMessagesMap:
                    lgMessagesMap[lg] = {};
                lgMessagesMap[lg][source] = {"source":m["source"], "tr":m["source"]}
        else:
            lgMessagesMap[lg] = lgCMs[lg][ct];

                
                
    for source in zhMessages:
        zhMessage = zhMessages[source]
        #print(source, zhMessage)
        if source in enMessages:
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
        toWrite += toWriteCt + "," + toWriteSource + "," + toWriteZhTr + "," + toWriteEnTr
        
        lgTr = {}     
        for lg in lgMessagesMap:
            if source in lgMessagesMap[lg]:
                lgMessage = lgMessagesMap[lg][source]
            lgTr[lg] = lgMessage["tr"]
            toW = ","
            if lgTr[lg] == None:
                toW += toWriteSource
            else:
                toW += '"' + lgMessage["tr"] + '"'
            toWrite += toW;
        toWrite += "\n"
        #print(toWriteCt, toWriteSource, toWriteZhTr, toWriteEnTr)

print(toWrite)
outputFile = open(sys.argv[3], 'w')
outputFile.write(toWrite)
outputFile.close()
