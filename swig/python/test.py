#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
"""

__author__ = 'Yuta Hayashibe' 
__version__ = ""
__copyright__ = ""
__license__ = "GPL v3"

import random
import unittest

import ncva

class Test(unittest.TestCase):
    def setUp(self):
        self.n = ncva.Ncva("/home/yuta-h/yucha-resource/ncv/bin/mainichi.1")
        pass

    def tearDown(self):
        pass


    def test_search(self):
        words = ["食べる", "笑う", "起こる", "無く"]

        for word in words:
            print self.n.get(word)



if __name__ == '__main__':
    unittest.main()
