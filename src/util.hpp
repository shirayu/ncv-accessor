/*
 * Copyright (c) Yuta Hayashibe
 * LICENSE : GNU GENERAL PUBLIC LICENSE Version 3
 *
 */


#ifndef HEADER_fc5133487d094ff382db2817342790b0
#define HEADER_fc5133487d094ff382db2817342790b0


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



};

#endif

