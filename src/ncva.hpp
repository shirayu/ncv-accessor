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
    const  std::string PREFIX_TRIE = ".trie";
    const  std::string PREFIX_FREQ = ".freq";
    const  std::string PREFIX_SUM = ".sum";

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
            void make(const char* name, const MAP_FREQUENCY &mymap, const FREQUENCY_LONG sum);

            const ID_t getID(const std::string &query) const;
            const std::vector<ID_t> getIDs(const std::string &query) const;
            const std::string getKey(const ID_t id) const;
            const FREQUENCY getFreq(const ID_t id) const;
            const FREQUENCY getFreq(const std::string &query) const;

            static int clean(const char*name);
    };

}

#endif

