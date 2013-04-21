/*
 *    Copyright Yusuke Tabata 2009 (tabata.yusuke@gmail.com)
 *
 * TODO: Add performance test.
 * TODO: Add test for large data set to cover corner cases.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <vector>
#include <string>
#include <fstream>

#include "ux/src/ux.hpp"

#include "cmdline.h"

void make(const char* output_name, std::istream *is){
    std::map<std::string, unsigned int> kvs;


    std::string buf;
    while(std::getline(*is, buf)) {
        const size_t sep = buf.find_first_of('\t');
        const size_t len = buf.size();
        const std::string word(buf, 0, sep);
        const std::string freq_str(buf, sep, len-sep);
        const unsigned int freq = atoi(freq_str.c_str());
    
        kvs[word] = freq;
    }

    
    ux::Map<unsigned int> uxm;
    uxm.build(kvs);

    std::ofstream os(output_name, std::ios::binary);
    uxm.save(os);
    os.close();
};


void read(const char* input_name){
    ux::Map<int> uxm2;
    std::ifstream ifs(input_name, std::ios::binary);
    uxm2.load(ifs);
//    for (std::map<std::string, unsigned int>::const_iterator it = kvs.begin();
//             it != kvs.end(); ++it){
//        std::string key = it->first;
//        int ret = -1;
//        std::cout << uxm2.get(key.c_str(), key.size(), ret) << std::endl;
//        std::cout << it->second << "\t" << ret << std::endl;
//    }
};


int main(int argc, char **argv) {
    cmdline::parser arg_parser;

//     add specified type of variable.
     // 1st argument is long name
     // 2nd argument is short name (no short name if '\0' specified)
     // 3rd argument is description
     // 4th argument is mandatory (optional. default is false)
     // 5th argument is default value  (optional. it used when mandatory is false)
     
    arg_parser.add<std::string>("output", 'o', "The filename to output", true, "");
    arg_parser.add<std::string>("input", 'i', "The filename to input.\n\t'-' means standard input is designated.", true, "");
        
    arg_parser.parse_check(argc, argv);

    const char* output_name = arg_parser.get<std::string>("output").c_str();
    std::string input = arg_parser.get<std::string>("input");
    std::istream *is = NULL;
    if (input == "-"){
        is = &std::cin;
    }
    else{
        is = new std::ifstream (input.c_str());
    };
    make(output_name, is);


    return 0;
}



