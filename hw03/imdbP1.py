# -*- coding: utf-8 -*-
"""This file contains code for use with "Python for Software Design",
available from Cambridge University Press, and "Think Python,"
available from greenteapress.com

Copyright 2010 Allen B. Downey
License: GNU GPLv3 http://www.gnu.org/licenses/gpl.html
"""

import sys
import os
import re
import bson
from pymongo import MongoClient

client = MongoClient()

db = client.imdb
actor = db.actor

def add_to_mongo(post):
    post_id = actor.insert(post)

def open_gunzip(filename):
    """open the filename, using a pipe and gunzip to read a
    compressed file without uncompressing the whole thing."""
    cmd = 'gunzip -c ' + filename
    fp = os.popen(cmd)
    return fp

def process_file(filename, f, num=10):
    dic = {}
    """read the given filename and extract information;
    for each film """
    
    fp = open_gunzip(filename)
    i = 0

    # skip over the header until you get to the following magic line
    for line in fp:
        if line.strip() == '----			------':
            break

    # regexp to recognize actor, tabs, movie
    split1 = re.compile('([^\t]*)\t*(.*)', re.UNICODE)

    # regexp to recognize title, date, role
    split2 = re.compile('([^\(]*)\s*(\([^\)]*\))[^\[]*(\[[^\]]*\])?', 
                        re.UNICODE)

    # regexp to recognize television (TV), video (V), video game (VG)
    video = re.compile('\(T?V|VG\)', re.U)
    # temp = open("temp","w")
    actor = ''
    for line in fp:
        line = line.rstrip()
        if line == '': continue
        if line[0] == '-----': break

        # split the line into actor info and movie info;
        # keep track of the current actor
        ro = split1.match(line)
        if ro:
            new_actor, info = ro.groups()
            if new_actor:
                actor = new_actor
        else:
            print 'BAD1', line
            continue

        # skip television shows (titles in quotation marks)
        if info[0] == '"':
            continue

        # skip made for TV and straight to video
        if video.search(info):
            continue

        # split the info into title, date and role
        ro = split2.match(info)
        if ro:
            title, date, role = ro.groups()
            title = title[:-1]
            try:
                unicode(actor)
                unicode(title)
            except:
                continue;
            if date == None:
                print 'BAD2', line
                continue;

            if i == 0:
                dic["name"]=actor
                dic["mov"]=[title]
            elif i != 0 and dic["name"] == actor:
                dic["mov"].append(title)
            else:
                add_to_mongo(dic)
                dic = {}
                dic = {"name":actor,"mov":[title]}

            i += 1
            if i > 100:
                break
        else:
            print 'BAD3', line
            continue

    stat = fp.close()


if __name__ == '__main__':
    def print_info(actor, title):
        print actor+"-"+title

    process_file('actors.list.gz', print_info)