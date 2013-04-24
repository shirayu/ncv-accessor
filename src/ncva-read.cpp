

#include "ncva.hpp"
#include "util.hpp"
#include "cmdline.h"


void read(const char* input_name){
    ncva::Ncva ncva(input_name);

    std::string buf;
    while(std::getline(std::cin, buf)) {
        const ncva::ID_t id = ncva.getID(buf);
        const ncva::FREQUENCY freq = ncva.getFreq(id);
        std::cout << freq << std::endl;
    };
};

void get_argscore(const char* input_name){
    ncva::Ncva ncva(input_name);

    std::string buf;
    while(std::getline(std::cin, buf)) {
        const std::vector<std::string> items = ncva::split(buf, ' ');
        const std::string &exp1 = items[0];
        const std::string &exp2 = items[1];
        const ncva::FREQUENCY freq1_base = ncva.getFreq(exp1);
        const ncva::FREQUENCY freq2_base = ncva.getFreq(exp2);
        const size_t exp1_size = exp1.size();
        const size_t exp2_size = exp2.size();

        const std::vector<ncva::ID_t> ids1 = ncva.getIDs(exp1);
        const std::vector<ncva::ID_t> ids2 = ncva.getIDs(exp2);
//        std::cerr << exp1 << " size(1) " << ids1.size() << std::endl;
//        std::cerr << exp2 << " size(2) " << ids2.size() << std::endl;


        std::map<std::string, double> nmap1;
        std::map<std::string, double> nmap2;
        for (std::vector<ncva::ID_t>::const_iterator it1 = ids1.begin(); it1 != ids1.end(); ++it1){
            const ncva::FREQUENCY freq1 = ncva.getFreq(*it1);
            const std::string key(ncva.getKey(*it1), exp1_size);
            nmap1[key] = (double) freq1 / freq1_base;
//            std::cerr << ncva.getKey(*it1) << "\t" << freq1  << "\t" << key << std::endl;
        };
        for (std::vector<ncva::ID_t>::const_iterator it2 = ids2.begin(); it2!=ids2.end(); ++it2){
            const ncva::FREQUENCY freq2 = ncva.getFreq(*it2);
            const std::string key(ncva.getKey(*it2), exp2_size);
            nmap2[key] = (double) freq2 / freq2_base;
//            std::cerr << ncva.getKey(*it2) << "\t" << freq2 << "\t" << key <<std::endl;
        };

        if(nmap1.size()==0 or nmap2.size()==0){
            std::cout << -1 << std::endl;
            continue;
        };
        const double val = ncva::JS(nmap1, nmap2);
        std::cout << val << "\t" << freq1_base << "\t" << freq2_base << std::endl;
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
    arg_parser.add("argscore", 'a', "Calc scores");

    arg_parser.parse_check(argc, argv);

    const char* input_name = arg_parser.get<std::string>("input").c_str();
    const bool argscore = arg_parser.exist("argscore");

    if (argscore){
        get_argscore(input_name);
    }
    else{
        read(input_name);
    };

    return 0;
}



