/*
 * Copyright (c) Yuta Hayashibe
 * LICENSE : GNU GENERAL PUBLIC LICENSE Version 3
 *
 */


#ifndef HEADER_fc5133487d094ff382db2817342790b0
#define HEADER_fc5133487d094ff382db2817342790b0

#include <cmath>


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


    //KL divergence
    template<typename L, typename M> double KL(const std::map<L, M> &P, const std::map<L,M> &Q){
        typedef typename std::map<L, M>::const_iterator LM_itr;
        double val=0;
        for(LM_itr it=P.begin(); it!=P.end(); ++it){
            if(Q.count(it->first)!=0){
                const double tmp = it->second / (double) Q.at(it->first);
                val +=  it->second  * log(tmp);
            };			
        };
        return val;
    };

    //JS divergence
    template<typename L, typename M> double JS(const std::map<L, M> &P, const std::map<L,M> &Q){
        typedef typename std::map<L, M>::const_iterator LM_itr;
        double val=0;
        for(LM_itr it=P.begin(); it!=P.end(); ++it){
            if(Q.count(it->first)==0){
                val +=  it->second  * log(2);
            }
            else{
                const double tmp = it->second / ( (double) Q.at(it->first) + it->second );
                val +=  it->second  * log(2 * tmp);
            };
        };
        for(LM_itr it=Q.begin(); it!=Q.end(); ++it){
            if(P.count(it->first)==0){
                val +=  it->second  * log(2);
            }
            else{
                const double tmp = it->second / ( (double) P.at(it->first) + it->second );
                val +=  it->second  * log(2 * tmp);
            };
        };
        return val / 2 ;

    };


};

#endif

