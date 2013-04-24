
#include "ncva.hpp"
#include "cmdline.h"


#include <fstream>


void read(const char* input_name){
    ncva::Ncva ncva(input_name);

    std::string buf;
    while(std::getline(std::cin, buf)) {
        const std::vector<ID_t> ids = ncva.getIDs(buf);
        
//        const FREQUENCY freq = ncva.getFreq(id);
        std::cout << ids.size() << std::endl;
    };
};


int main(int argc, char **argv) {
    cmdline::parser arg_parser;

    arg_parser.add<std::string>("input", 'i', "The filename to input.\n\t'-' means standard input is designated.", true, "");

    arg_parser.parse_check(argc, argv);

    const char* input_name = arg_parser.get<std::string>("input").c_str();
    read(input_name);

    return 0;
}



