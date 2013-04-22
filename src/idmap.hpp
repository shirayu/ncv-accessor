/*
 * Copyright (c) Yuta Hayashibe
 * LICENSE : GNU GENERAL PUBLIC LICENSE Version 3
 *
 */


#include "common.hpp"

#ifndef HEADER_07dac634bf914f689fb8c04045b89859
#define HEADER_07dac634bf914f689fb8c04045b89859


namespace ncva{

    class IdMap{
        public:
            IdMap();

            void build(const Trie &trie, MAP_FREQUENCY &freq_map);
            void save(const char* filename);
            FREQUENCY Idmap::get(const ncva::id_t id);
    };

};

#endif

