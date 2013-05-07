/*
 * Copyright (c) Yuta Hayashibe
 * LICENSE : GNU GENERAL PUBLIC LICENSE Version 3
 *
 */


#include "common.hpp"
#include "fstream"

#include "mmap.h"

#ifndef HEADER_fe0226c0ea8e42d693276dbdb06f7a67
#define HEADER_fe0226c0ea8e42d693276dbdb06f7a67


namespace ncva{
    class ArrayImpl {
        public:
            virtual ~ArrayImpl(){};
            virtual void save() = 0;
            virtual FREQUENCY get(const ID_t id) = 0;
            virtual void add(FREQUENCY freq) = 0;
    };


    class Array {
        private:
            ArrayImpl *impl;
        public:
            Array(ArrayImpl *impl) : impl(impl){
            };
            void save(){
                this->impl->save();
            };
            FREQUENCY get(const ID_t id){
                return this->impl->get(id);
            };
            void add(FREQUENCY freq){
                this->impl->add(freq);
            };
    };


    class NaiveArray : public ArrayImpl{
        protected:
            whatlog what_;

        private:
//            std::ifstream *ifs;
            Mmap<FREQUENCY> *mmap_;
            std::ofstream *ofs;
            size_t filesize;
        public:
            NaiveArray(const char *filename, const bool write);
            bool open(const char *filename);
            ~NaiveArray();
            void save();
            FREQUENCY get(const ID_t id);
            void add(FREQUENCY freq);
    };


};

#endif

