#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def buildData(contexts):
    ret = {}
    for ct in contexts:
        lineToMessageMap = {}
        messages = ct.findall("message")
        for m in messages:
            type = m.find("translation")
            tr = type.text
            type = type.attrib
            if "type" in type:
                type = type["type"]
            else:
                type = ""
            if type != "obsolete":
                source = str(m.find("source").text)
                lineToMessageMap[source] = {"source":source, "tr":tr}
        ret[ct.find("name").text] = lineToMessageMap
    #print(ret)
    return ret
