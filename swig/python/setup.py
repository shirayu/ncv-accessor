#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
"""

from distutils.core import setup, Extension

ext_module = Extension('_ncva',
                       sources=[ 'ncva_wrap.cxx'],
                       libraries=["stdc++"],
                       extra_objects = ['../../bin/libncva.a', '../../bin/libux.a'],
                       include_dirs = ['../../src/'],
                       )

setup(name='ncva-python',
      version='0.1',
      author='Yuta Hayashibe',
#      author_email='',
      ext_modules=[ext_module],
      py_modules=['ncva'],
      )

