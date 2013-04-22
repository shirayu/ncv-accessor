/*
 * Copyright (c) Yuta Hayashibe
 * LICENSE : GNU GENERAL PUBLIC LICENSE Version 3
 *
 */

#include <fstream>
#include "ux/src/ux.hpp"

#ifndef HEADER_141dfa9c1ed7469d8b53cefb442db7d3
#define HEADER_141dfa9c1ed7469d8b53cefb442db7d3


namespace ncva{
    void build(const MAP_FREQUENCY &map_ncv, const MAP_FREQUENCY &map_cvn, const FREQUENCY sum){

    };

//    void save(const char * output_name){
//        std::ofstream os(output_name, std::ios::binary);
//        ux_ncv.save(os);
//        os.close();
//    };

    class Ncva{
			private:
				ux::Trie ux_ncv;
				ux::Trie ux_vnc;
                FREQUENCY_LONG SUM;

			public:
				Ncva() : ux_ncv(), ux_vnc(){
                };
				~Ncva(){
				};
    };


};
#endif

