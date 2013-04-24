/*
 * Copyright (c) Yuta Hayashibe
 * LICENSE : GNU GENERAL PUBLIC LICENSE Version 3
 *
 */


#include "common.hpp"

#ifndef HEADER_489c0b4bffc04092b46c7b9ad067af19
#define HEADER_489c0b4bffc04092b46c7b9ad067af19

#include "../ux/src/ux.hpp"

namespace ncva{
    class TrieImpl {
        public:
            virtual ~TrieImpl(){};
            virtual void save(const char *filename) = 0;
            virtual void build(std::vector<std::string>& keyList) = 0;
            virtual ID_t getID(const std::string &query) = 0;
            virtual const std::string getKey(const ID_t id) = 0;
            virtual ID_t size() = 0;
            virtual std::vector<ID_t> getIDs(const std::string &query) = 0;
    };


    class Trie {
        private:
            TrieImpl *impl;
        public:
            Trie(TrieImpl *impl) : impl(impl){
            };
            void save(const char *filename){
                this->impl->save(filename);
            };
            void build(std::vector<std::string>& keyList){
                this->impl->build(keyList);
            };
            ID_t getID(const std::string &query){
                return this->impl->getID(query);
            };
            const std::string getKey(const ID_t id){
                return this->impl->getKey(id);
            };
            ID_t size(){
                return this->impl->size();
            };
            std::vector<ID_t> getIDs(const std::string &query){
                return this->impl->getIDs(query);
            };;
    };


    class UxTrie : public TrieImpl{
        private:
            ux::Trie *trie;
        public:
            UxTrie(const char *filename);
            ~UxTrie();
            void save(const char *filename);
            void build(std::vector<std::string>& keyList);
            ID_t getID(const std::string &query);
            const std::string getKey(const ID_t id);
            ID_t size();
            std::vector<ID_t> getIDs(const std::string &query);
    };


};

#endif

