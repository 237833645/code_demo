#!/bin/python
# -*- coding: UTF-8 -*-

import os
testfiles = []
testfilepaths = []
L = len(os.path.abspath('.'))

def searchfile(fname, path):
    for item in os.listdir(path):
        if os.path.isdir(os.path.join(path, item)):
            searchfile(fname, os.path.join(path, item))
        else:
            if fname in item:
                print(item, path[L:])
            

searchfile('.py',os.path.abspath('.'))


