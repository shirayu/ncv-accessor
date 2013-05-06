
//#include "ncva.hpp"

#include "common.hpp"
#include "cmdline.h"


#include <fstream>

#include "ncva.hpp"
#include "util.hpp"

namespace ncva{

    void make(const char* output_name, std::istream *is, const uint32_t line_num, const int mode){
        MAP_FREQUENCY mymap;
        FREQUENCY_LONG sum = 0;
        uint32_t step = 0;
        FREQUENCY freq = 0;

        std::string buf;
        while(std::getline(*is, buf)) {
            if(step % 100000 == 0){
                fprintf(stderr, "\rStatus : %u", step);
                if (line_num != 0){
                    const double percent = (double) step / line_num * 100;
                    fprintf(stderr, "  %0.3f%%", percent);
                };
            };

            if (mode == 0 or mode == 1){
                const std::vector<std::string> items = split(buf, '\t');
                if (items.size() != 4){
                    std::cerr << "Error at " << step << std::endl;
                    continue;
                };

                const std::string& noun = items[0];
                const std::string& particle = items[1];
                const std::string& verb = items[2];
                const std::string& freq_word = items[3];
                freq = atoi(freq_word.c_str()); //FIXME change to strtol
            
                if (mode == 1){
                    mymap[verb] += freq;
                    mymap[verb + "\t" + particle ] += freq;
                    mymap[verb + "\t" + particle + "\t" + noun] += freq;
                }
                else{
                    mymap[noun] += freq;
                    mymap[noun + "\t" + particle ] += freq;
                    mymap[noun + "\t" + particle + "\t" + verb] += freq;
                };
            }
            else if(mode==2){
                for(size_t i= buf.size()-1; i>=0; --i){
                    if(buf[i] == '\t'){
                        freq = atoi(buf.substr(i+1).c_str());
                        mymap[buf.substr(0, i)] = freq;
    std::cerr << freq  << "|\t|" << buf.substr(0, i) << "|" << std::endl;
                        break;
                    };
                };

            }
            else{
            };
            sum += freq;

            ++step;
        }
      
        ncva::Ncva ncva;
        ncva.make(output_name, mymap, sum);
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
     
    arg_parser.add<std::string>("output", 'o', "The filename to output", true, "");
    arg_parser.add<std::string>("input", 'i', "The filename to input.\n\t'-' means standard input is designated.", true, "");
    arg_parser.add<uint32_t>("lines", 'l', "The number of line", false, 0);
    arg_parser.add<int>("mode", 'm', "Switch the mode", true, 0);

        
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
    const uint32_t line_num = arg_parser.get<uint32_t>("lines");
    const int mode = arg_parser.get<int>("mode");
    std::cerr << "Mode is " << mode << std::endl;
    ncva::make(output_name, is, line_num, mode);


    return 0;
}



