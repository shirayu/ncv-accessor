
#include "ncva.hpp"

#include <stdio.h>

namespace ncva{

    Ncva::Ncva() : mytrie(NULL), myarray(NULL), sum(0){
    };

    Ncva::Ncva(const char* name) : mytrie(NULL), myarray(NULL), sum(0){
        const std::string in_trie = std::string(name) + ncva::PREFIX_TRIE;
        const std::string in_freq = std::string(name) + ncva::PREFIX_FREQ;
        const std::string in_sum = std::string(name) + ncva::PREFIX_SUM;

        this->mytrie = new ncva::Trie(new ncva::UxTrie(in_trie.c_str()));
        this->myarray = new ncva::Array(new ncva::NaiveArray(in_freq.c_str(), false));

        std::ifstream ifs(in_sum.c_str());
        ifs >> sum;
        ifs.close();
    };


    void Ncva::make(const char* name, const MAP_FREQUENCY &mymap, const FREQUENCY_LONG sum){
        const std::string out_trie = std::string(name) + ncva::PREFIX_TRIE;
        const std::string out_freq = std::string(name) + ncva::PREFIX_FREQ;
        const std::string out_sum = std::string(name) + ncva::PREFIX_SUM;

        std::ofstream out_f(out_sum.c_str());
        out_f << sum;
        out_f.close();
        
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
        ncva::Array myarray(new ncva::NaiveArray(out_freq.c_str(), true));

		const size_t max = mytrie.size();
		for(size_t id=0; id!=max; ++id){
			const std::string key = mytrie.getKey(id);
            const MAP_FREQUENCY::const_iterator ret = mymap.find(key);
            if(ret != mymap.end()){
                const FREQUENCY freq = ret->second;
                myarray.add(freq);
            }
            else{
                myarray.add(0);
            };
        };
        myarray.save();
    }


    const ID_t Ncva::getID(const std::string &query) const{
        return this->mytrie->getID(query);
    };


    const std::vector<ID_t> Ncva::getIDs(const std::string &query) const{
        return this->mytrie->getIDs(query);
    };

    const std::string Ncva::getKey(const ID_t id) const{
        return this->mytrie->getKey(id);
    };

    const FREQUENCY Ncva::getFreq(const ID_t id) const{
        return this->myarray->get(id);
    };

    const FREQUENCY Ncva::getFreq(const std::string &query) const{
        const ID_t id = this->getID(query);
        return this->getFreq(id);
    };

    int Ncva::clean(const char*name){
        const std::string in_trie = std::string(name) + ncva::PREFIX_TRIE;
        const std::string in_freq = std::string(name) + ncva::PREFIX_FREQ;
        const std::string in_sum = std::string(name) + ncva::PREFIX_SUM;

        const bool ret1 = remove(in_trie.c_str());
        const bool ret2 = remove(in_freq.c_str());
        const bool ret3 = remove(in_sum.c_str());
        return ret1 and ret2 and ret3;
    };

};
