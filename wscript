#!/usr/bin/env python
# encoding: utf-8

# Copyright (c) Yuta Hayashibe
# LICENSE : GNU GENERAL PUBLIC LICENSE Version 3


APPNAME = 'yucha'
VERSION = '1.87'

#srcdir = 'src'
out = 'bin'

def options(opt):
    opt.tool_options('compiler_cxx')
    opt.tool_options('compiler_cc')
    opt.tool_options('daemon', tooldir='tool')
    opt.add_option( '--debug'
        , action='store_true'
        , default=False
        , help='Enable debug mode [Default: False]'
        , dest='debug'
    )
    opt.add_option( '--prof'
        , action='store_true'
        , default=False
        , help='Enable profiling mode [Default: False]'
        , dest='prof'
    )

    #
    opt.load('compiler_cxx')
    opt.load('unittest_gtest')


def configure(conf):
    conf.load('compiler_cxx')
    conf.load('unittest_gtest')

    conf.check_tool('compiler_cxx')
    conf.check_tool('compiler_cc')
    _ccv = conf.env['CC_VERSION']

    conf.check_tool('daemon', tooldir='tool')

    import Options
    conf.env["PROF_MODE"] = Options.options.prof
    if conf.env['PROF_MODE'] == True:
        conf.env.append_value('CPPFLAGS', '-pg')
        conf.env.append_value('LINKFLAGS', '-pg')
    conf.env["DEBUG_MODE"] = Options.options.debug

    import datetime
    d = datetime.datetime.today()
    DATETIME = d.strftime("%Y-%m-%d %H:%M:%S")
    conf.define("CONST_YUCHA_VERSION", VERSION)
    conf.define("CONST_COMF_DATETIME", DATETIME)


def build(bld):
    INCS  = ['ux/src']
    if bld.env['PROF_MODE']:
        CXXFLAGS = ['-g', '-pg', '-Wall'] #,'-Wshadow']
    elif bld.env['DEBUG_MODE']:
        CXXFLAGS = ['-gstabs+', '-O0', '-Wall'] #,'-Wshadow']
    else:
        CXXFLAGS = ['-O3', '-Wall'] #,'-Wshadow']

    bld(
       features = 'cxx cxxstlib',
       source       = ['ux/src/uxTrie.cpp', 'ux/src/bitVec.cpp',
                        'ux/src/rsDic.cpp',  'ux/src/uxUtil.cpp', 'ux/src/uxMap.cpp',],
       target       = 'ux',
       name         = 'UX',
       includes     = './')

    bld(features = 'cxx cprogram',
        source = ['ncva-make.cpp', 'trie.cpp'],
        target = 'ncva-make',
        cxxflags     = CXXFLAGS,
        use = [
            'UX',
         ],
    )

