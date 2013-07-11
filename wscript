#!/usr/bin/env python
# encoding: utf-8

# Copyright (c) Yuta Hayashibe
# LICENSE : GNU GENERAL PUBLIC LICENSE Version 3


APPNAME = 'ncva'
VERSION = '0.2'

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


    #for mmap
    conf.check_cxx(header_name = 'sys/types.h')
    conf.check_cxx(header_name = 'sys/stat.h')
    conf.check_cxx(header_name = 'fcntl.h')
    conf.check_cxx(header_name = 'string.h')
    conf.check_cxx(header_name = 'windows.h', mandatory=False)
    conf.check_cxx(header_name = 'sys/mman.h')
    conf.check_cxx(header_name = 'unistd.h')
    conf.define('HAVE_CONFIG_H', 1)
    conf.define('HAVE_MMAP', 1)
    ###


    conf.write_config_header('../src/config.h')

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
        cxxflags     = CXXFLAGS + ['-fPIC'],
       name         = 'UX',
       includes     = './')

    bld(
        features = 'cxx cxxstlib',
        source = ['src/ncva.cpp', 'src/trie.cpp', 'src/array.cpp'],
        target = 'ncva',
        cxxflags     = CXXFLAGS + ['-fPIC'],
        use = [
            'UX',
         ],
        includes = 'ux/src/',
        name = 'NCVA',
    )

    bld(features = 'cxx cprogram',
        source = ['src/ncva-make.cpp'],
        target = 'ncva-make',
        cxxflags     = CXXFLAGS,
        use = [ 'NCVA', ],
    )

    bld(features = 'cxx cprogram',
        source = ['src/ncva-read.cpp'],
        target = 'ncva-read',
        cxxflags     = CXXFLAGS,
        use = [ 'NCVA', ],
    )

    bld.program(
            features     = 'gtest',
            source = ['src/trie-test.cpp', 'src/trie.cpp', 'src/array.cpp'],
            target = 'trie-test',
            cxxflags     = CXXFLAGS,
            use = [ 'UX', ],
    )
    bld.program(
            features     = 'gtest',
            source = ['src/array-test.cpp', 'src/trie.cpp', 'src/array.cpp'],
            target = 'array-test',
            cxxflags     = CXXFLAGS,
            use = [ 'UX', ],
    )

    bld.program(
            features     = 'gtest',
            source = ['src/ncva-test.cpp', 'src/ncva.cpp', 'src/trie.cpp', 'src/array.cpp'],
            target = 'ncva-test',
            cxxflags     = CXXFLAGS,
            use = [ 'UX', ],
    )

