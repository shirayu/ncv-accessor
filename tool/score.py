#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
"""
__author__ = 'Yuta Hayashibe' 
__version__ = ""
__copyright__ = ""
__license__ = "GPL v3"

import sys
import re

CASES = ['が', 'を', 'に']

if __name__=='__main__':
    import optparse
    oparser = optparse.OptionParser()
    oparser.add_option('-i', dest = 'input', help='')
    oparser.add_option('-n', dest = 'num', type="int", help='')
    oparser.add_option('-R', dest = 'root', type="int", help='')
    (opts, args) = oparser.parse_args()


    if opts.input and opts.num is not None and opts.root:
        words = []
        for line in open(opts.input).readlines():
            word = line.rstrip().split("\t")[1]
            words.append(word)

        total = len(words)
        split_num = total / opts.root
        start = split_num * opts.num

        for word1 in words[start : start+split_num]:
            for word2 in words:
#                for case1 in CASES:
#                    for case2 in CASES:
#                        print "%s\t%s %s\t%s" % (word1, case1, word2, case2)
                print "%s\t%s\t%s" % (word1, case1, word2, )




