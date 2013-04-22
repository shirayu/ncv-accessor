
//#include "ncva.hpp"

#include "common.hpp"
#include "cmdline.h"


#include <fstream>

#include "trie.hpp"

namespace ncva{
    std::vector<std::string> split(const std::string &str, const char delim){
        std::vector<std::string> res;
        size_t current = 0;
        size_t found = 0;
        while((found = str.find_first_of(delim, current)) != std::string::npos){
            res.push_back(std::string(str, current, found - current));
            current = found + 1;
        }
        res.push_back(std::string(str, current, str.size() - current));
        return res;
    }

    void make(const char* output_name, std::istream *is, const unsigned int line_num, const bool mode_VCN){
        MAP_FREQUENCY mymap;
        FREQUENCY_LONG sum = 0;
        FREQUENCY_LONG step = 0;

        std::string buf;
        while(std::getline(*is, buf)) {
            const std::vector<std::string> items = split(buf, '\t');
            if (items.size() != 4){
                std::cerr << "Error at " << step << std::endl;
                continue;
            };
            if(step % 100000 == 0){
                fprintf(stderr, "\rStatus : %lu", step);
                if (line_num != 0){
                    const double percent = (double) step / line_num * 100;
                    fprintf(stderr, "  %0.3f%%", percent);
                };
            };

            const std::string& noun = items[0];
            const std::string& particle = items[1];
            const std::string& verb = items[2];
            const std::string& freq_word = items[3];
            const FREQUENCY freq = atoi(freq_word.c_str());
        
            if (mode_VCN){
                mymap[verb] += freq;
                mymap[verb + "\t" + particle ] += freq;
                mymap[verb + "\t" + particle + "\t" + noun] += freq;
            }
            else{
                mymap[noun] += freq;
                mymap[noun + "\t" + particle ] += freq;
                mymap[noun + "\t" + particle + "\t" + verb] += freq;
            };
            sum += freq;

            ++step;
        }
       
        /////
        const std::string out_freq = std::string(output_name) + ".freq";
        const std::string out_trie = std::string(output_name) + ".trie";
        std::vector<std::string> tmp;
        tmp.reserve(mymap.size());

        std::cerr << "Extracting words..." << std::endl;
        for(MAP_FREQUENCY::const_iterator it=mymap.begin(); it!=mymap.end(); ++it){
            tmp.push_back(it->first);
        };

	    std::cerr << "Making trie..." << std::endl;
        ncva::Trie mytrie(new ncva::UxTrie(NULL));
        mytrie.build(tmp);
        mytrie.save(out_trie.c_str());

	    std::cerr << "Making freq..." << std::endl;
		std::ofstream freqfile(out_freq.c_str(), std::ios::binary);

		const size_t max = mytrie.size();
		for(size_t id=0; id!=max; ++id){
			const std::string key = mytrie.getKey(id);
            const FREQUENCY freq = mymap[key];
			freqfile.write((char*) &(freq), sizeof(FREQUENCY));
        };
        freqfile.close();
    };

      
    void read(const char* input_name){
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
    arg_parser.add<unsigned int>("lines", 'l', "The number of line", false, 0);
    arg_parser.add<bool>("mode", 'n', "Switch the mode", false, true);
        
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
    const unsigned int line_num = arg_parser.get<unsigned int>("lines");
    const bool mode = arg_parser.get<bool>("mode");
    ncva::make(output_name, is, line_num, mode);


    return 0;
}



