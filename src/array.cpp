/*
 * Copyright (c) Yuta Hayashibe
 * LICENSE : GNU GENERAL PUBLIC LICENSE Version 3
 *
 */

#include "common.hpp"
#include "array.hpp"

#include "mmap.h"

namespace ncva{


    NaiveArray::NaiveArray(const char *filename, const bool write) : mmap_(NULL), ofs(NULL), filesize(0){
        if (filename == NULL){
        }
        else{
            if (write){
        		this->ofs = new std::ofstream(filename, std::ios::binary);
            }
            else{
                this->open(filename);
            };
        };
    };

    bool NaiveArray::open(const char *filename){
        this->mmap_ = new Mmap<FREQUENCY>;
        CHECK_FALSE(mmap_->open(filename)) <<  mmap_->what();
        this->filesize = this->mmap_->size();
        //                this->mmap->seekg(0, std::ios::beg);  
        return true;
    };

    NaiveArray::~NaiveArray(){
        delete this->mmap_;
        delete this->ofs;
    };

    void NaiveArray::save(){
        if (this->ofs != NULL){
            this->ofs->flush();
        };
    };

    FREQUENCY NaiveArray::get(const ID_t id){
//        const size_t position = sizeof(FREQUENCY) * id;
        const size_t position = id;
        if (position < this->filesize){
            return (*(this->mmap_))[position];
//            mmap_->seekg(position, std::ios_base::beg);
//            FREQUENCY freq;
//            mmap_->read((char *) &freq, sizeof(FREQUENCY));
//            return freq;
        };
        return 0;
    };

    void NaiveArray::add(FREQUENCY freq){
		this->ofs->write((char*) &(freq), sizeof(FREQUENCY));
    };

};
