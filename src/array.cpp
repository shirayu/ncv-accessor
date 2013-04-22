/*
 * Copyright (c) Yuta Hayashibe
 * LICENSE : GNU GENERAL PUBLIC LICENSE Version 3
 *
 */

#include "common.hpp"
#include "array.hpp"

namespace ncva{


    NaiveArray::NaiveArray(const char *filename, const bool write) : ifs(NULL), ofs(NULL){
        if (filename == NULL){
        }
        else{
            if (write){
        		this->ofs = new std::ofstream(filename, std::ios::binary);
            }
            else{
        		this->ifs = new std::ifstream(filename, std::ios::binary);
            };
        };
    };

    NaiveArray::~NaiveArray(){
        delete this->ifs;
        delete this->ofs;
    };

    void NaiveArray::save(){
        //do nothing
    };

    FREQUENCY NaiveArray::get(const ID_t id){
        return 0;
    };

    void NaiveArray::add(FREQUENCY freq){
		this->ofs->write((char*) &(freq), sizeof(FREQUENCY));
    };

};
