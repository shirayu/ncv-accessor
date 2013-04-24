/*
 * Copyright (c) Yuta Hayashibe
 * LICENSE : GNU GENERAL PUBLIC LICENSE Version 3
 *
 */


#include "array.hpp"
#include <gtest/gtest.h>

#include <stdio.h>

const char tempname[] = ".tmp";

TEST(array, make){
    std::vector<ncva::FREQUENCY> tmp;
    const ncva::FREQUENCY val0 = 12;
    const ncva::FREQUENCY val1 = 345;
    const ncva::FREQUENCY val2 = 6789012;
    tmp.push_back(val0);
    tmp.push_back(val1);
    tmp.push_back(val2);

    ncva::Array myarray(new ncva::NaiveArray(tempname, true));
    for (std::vector<ncva::FREQUENCY>::const_iterator it = tmp.begin(); it != tmp.end(); ++it){
        myarray.add(*it);
    };
    myarray.save();

    ncva::Array myarray2(new ncva::NaiveArray(tempname, false));
    ASSERT_EQ(val0, myarray2.get(0));
    ASSERT_EQ(val1, myarray2.get(1));
    ASSERT_EQ(val2, myarray2.get(2));

    remove(tempname);
}


