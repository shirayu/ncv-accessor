
//#include "ncva.hpp"

#include "common.hpp"
#include "cmdline.h"


#include <fstream>

#include "trie.hpp"
#include "array.hpp"

namespace ncva{
    void read(const char* input_name){
        const std::string in_trie = std::string(input_name) + ".trie";
        const std::string in_freq = std::string(input_name) + ".freq";

        ncva::Trie mytrie(new ncva::UxTrie(in_trie.c_str()));
        ncva::Array myarray(new ncva::NaiveArray(in_freq.c_str(), false));

        std::string buf;
        while(std::getline(std::cin, buf)) {
            const ID_t id = mytrie.getID(buf);
            const FREQUENCY freq = myarray.get(id);
            std::cout << id << "\t" << freq << std::endl;
        };
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
    ncva::read(input_name);

    return 0;
}



