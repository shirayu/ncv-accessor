/*
 * Copyright (c) Yuta Hayashibe
 * LICENSE : GNU GENERAL PUBLIC LICENSE Version 3
 *
 */

#include "common.hpp"
#include "trie.hpp"

namespace ncva{

        UxTrie::UxTrie(const char *filename) : trie(NULL){
            this->trie = new ux::Trie;
            if (filename != NULL){
                this->trie->load(filename);
            };
        };

        UxTrie::~UxTrie(){
            delete this->trie;
        };

        void UxTrie::build(std::vector<std::string>& keyList){
            this->trie->build(keyList);
        };

        void UxTrie::save(const char *filename){
            this->trie->save(filename);
        };

        ID_t UxTrie::getID(const std::string &query){
			size_t retLen = 0;
            const size_t query_size = query.size();
			const ID_t id = this->trie->prefixSearch(query.c_str(), query_size, retLen);

            if (retLen == query_size){
                return id;
            }
            return ncva::NOTFOUND;
        };

        std::vector<ID_t> UxTrie::getIDs(const std::string &query){
            std::vector<ID_t> retIDs;
            const size_t query_size = query.size();
//            const size_t retLen = ;
            this->trie->predictiveSearch(query.c_str(), query_size, retIDs);
            return retIDs;
        };

        const std::string UxTrie::getKey(const ID_t id){
		    const std::string key = this->trie->decodeKey(id);
            return key;
        };

        ID_t UxTrie::size(){
            return this->trie->size();
        };
};
