
//#include "ncva.hpp"

#include "common.hpp"
#include "cmdline.h"


#include <fstream>

#include "ncva.hpp"

void read(const char* input_name){
    ncva::Ncva ncva(input_name);

    std::string buf;
    while(std::getline(std::cin, buf)) {
        const ncva::ID_t id = ncva.getID(buf);
        const ncva::FREQUENCY freq = ncva.getFreq(id);
        std::cout << freq << std::endl;
    };
};


int main(int argc, char **argv) {
    cmdline::parser arg_parser;

//     add specified type of variable.
     // 1st argument is long name
     // 2nd argument is short name (no short name if '\0' specified)
     // 3rd argument is description
     // 4th argument is mandatory (optional. default is false)
     // 5th argument is default value  (optional. it used when mandatory is false)
     
    arg_parser.add<std::string>("input", 'i', "The filename to input.\n\t'-' means standard input is designated.", true, "");
        
    arg_parser.parse_check(argc, argv);

    const char* input_name = arg_parser.get<std::string>("input").c_str();
    read(input_name);

    return 0;
}



