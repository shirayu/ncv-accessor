/*
 * Copyright (c) Yuta Hayashibe
 * LICENSE : GNU GENERAL PUBLIC LICENSE Version 3
 *
 */

#include "common.hpp"
#include "array.hpp"

namespace ncva{


    NaiveArray::NaiveArray(const char *filename, const bool write) : ifs(NULL), ofs(NULL), filesize(0){
        if (filename == NULL){
        }
        else{
            if (write){
        		this->ofs = new std::ofstream(filename, std::ios::binary);
            }
            else{
        		this->ifs = new std::ifstream(filename, std::ios::binary);
                this->filesize = (size_t) this->ifs->seekg(0, std::ios::end).tellg();
                this->ifs->seekg(0, std::ios::beg);  
            };
        };
    };

    NaiveArray::~NaiveArray(){
        delete this->ifs;
        delete this->ofs;
    };

    void NaiveArray::save(){
        if (this->ofs != NULL){
            this->ofs->flush();
        };
    };

    FREQUENCY NaiveArray::get(const ID_t id){
        const size_t position = sizeof(FREQUENCY) * id;
        if (position < this->filesize){
            ifs->seekg(position, std::ios_base::beg);
            FREQUENCY freq;
            ifs->read((char *) &freq, sizeof(FREQUENCY));
            return freq;
        };
        return 0;
    };

    void NaiveArray::add(FREQUENCY freq){
		this->ofs->write((char*) &(freq), sizeof(FREQUENCY));
    };

};
