/*
 * Copyright (c) Yuta Hayashibe
 * LICENSE : GNU GENERAL PUBLIC LICENSE Version 3
 *
 */


#ifndef HEADER_141dfa9c1ed7469d8b53cefb442db7d3
#define HEADER_141dfa9c1ed7469d8b53cefb442db7d3

#include "trie.hpp"
#include "array.hpp"
#include "common.hpp"

namespace ncva{
    const static std::string PREFIX_TRIE = ".trie";
    const static std::string PREFIX_FREQ = ".freq";
    const static std::string PREFIX_SUM = ".sum";

    class Ncva{
        private:
            ncva::Trie *mytrie;
            ncva::Array *myarray;
            FREQUENCY_LONG sum;
        public:
            Ncva();
            Ncva(const char* name);
            ~Ncva(){
                delete this->mytrie;
                delete this->myarray;
            };
            void open(const char* name);
            void make(const char* name, const ncva::MAP_FREQUENCY &mymap, const ncva::FREQUENCY_LONG sum);

            const ID_t getID(const std::string &query) const;
            const FREQUENCY getFreq(const ncva::ID_t id) const;
            const FREQUENCY getFreq(const std::string &query) const;

            static int clean(const char*name);
    };

}

#endif

