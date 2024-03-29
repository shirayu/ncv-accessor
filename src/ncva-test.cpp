/*
 * Copyright (c) Yuta Hayashibe
 * LICENSE : GNU GENERAL PUBLIC LICENSE Version 3
 *
 */


#include "ncva.hpp"
#include <gtest/gtest.h>

#include <stdio.h>

const char tempname[] = "3ab8b0ce-e9b8-4a9c-b4e3-77fd46442801";

TEST(array, make){
    ncva::MAP_FREQUENCY mymap;
    const ncva::FREQUENCY f0 = 98000;
    const ncva::FREQUENCY f1 = 765;
    const ncva::FREQUENCY_LONG sum = f0+ f1;
    mymap["orange"] = f0;
    mymap["tomato"] = f1;

    ncva::Ncva ncva;
    ncva.make(tempname, mymap, sum);

    ncva::Ncva ncva2(tempname);
    ASSERT_NE(ncva2.getID("orange"), ncva2.getID("tomato"));
    ASSERT_NE(ncva2.getID("orange"), ncva2.getID("apple"));
    ASSERT_EQ(ncva2.getID("banana"), ncva2.getID("apple"));

    ASSERT_EQ(ncva2.getFreq(ncva2.getID("banana")), (ncva::FREQUENCY) 0);
    ASSERT_EQ(ncva2.getFreq(ncva2.getID("orange")), f0);
    ASSERT_EQ(ncva2.getFreq(ncva2.getID("tomato")), f1);

    ASSERT_EQ(ncva2.getFreq("banana"), (ncva::FREQUENCY) 0);
    ASSERT_EQ(ncva2.getFreq("orange"), f0);
    ASSERT_EQ(ncva2.getFreq("tomato"), f1);

    ASSERT_EQ(ncva2.getSum(), sum);

    const int ret = ncva::Ncva::clean(tempname);
    ASSERT_EQ(ret, 0);

}


