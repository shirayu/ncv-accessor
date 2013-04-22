/*
 * Copyright (c) Yuta Hayashibe
 * LICENSE : GNU GENERAL PUBLIC LICENSE Version 3
 *
 */

#include <tr1/unordered_map>

#include <stdint.h>

#ifndef HEADER_ad8d275923a44807ad6fd9621b1e83b5
#define HEADER_ad8d275923a44807ad6fd9621b1e83b5


namespace ncva{
    typedef unsigned int FREQUENCY;
    typedef unsigned long int FREQUENCY_LONG;
    typedef std::tr1::unordered_map<std::string, FREQUENCY> MAP_FREQUENCY;

    typedef uint64_t ID_t;

};

#endif

