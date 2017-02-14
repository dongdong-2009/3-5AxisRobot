#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import sys
import xml.etree.ElementTree as ET
import xlrd
#from utils import *


if len(sys.argv) < 4:
    print("Usage: python3 csvtots.py cusTS target_ts out_file lenLimit")
    exit

inTargetTs = ET.parse(sys.argv[2])
inTargetContexts = inTargetTs.getroot().findall("context")

cusTs = xlrd.open_workbook(sys.argv[1])

tsedInfo = {}
for booksheet in cusTs.sheets():
    messageInfo = {}
    for row in range(booksheet.nrows):
        ct = booksheet.cell(row, 0).value
        source = str(booksheet.cell(row, 1).value)
        zhTr = str(booksheet.cell(row, 2).value)
        enTr = str(booksheet.cell(row, 3).value)
        tr = booksheet.cell(row, 4).value
        if ct not in tsedInfo:
            tsedInfo[ct] = {}
        tsedInfo[ct][source] = {"source":source, "tr":tr, "zhtrcount":len(enTr) + int(sys.argv[4])}
#print(tsedInfo)
#        for col in range(booksheet.ncols):
#            print(booksheet.cell(row, col).value)


for ct in inTargetContexts:
    ctName = ct.find("name").text
    if ctName in tsedInfo:
        messages = ct.findall("message")
        tsedMessageInfo = tsedInfo[ctName]
        for m in messages:
            source = str(m.find("source").text)
            if source in tsedMessageInfo:
                tr = str(tsedMessageInfo[source]["tr"])
                trlen = len(tr)
                if trlen <= tsedMessageInfo[source]["zhtrcount"]:
                    m.find("translation").text = tr
                else:
                    m.find("translation").text = tr[0:int(trlen / 2)] + "-\n" + tr[int(trlen / 2):]

inTargetTs.write(sys.argv[3], "UTF-8", True)
