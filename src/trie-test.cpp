/*
 * Copyright (c) Yuta Hayashibe
 * LICENSE : GNU GENERAL PUBLIC LICENSE Version 3
 *
 */


#include "ncva.hpp"
#include <gtest/gtest.h>

#include <stdio.h>

const std::string tempname = "30eb64bf-32f0-4064-9855-75c693a37c3c";

TEST(trie, make){
    std::vector<std::string> tmp;
    const char str1[] = "\xE6\x84\x9B\xE6\x83\x85"; //愛情
    const char str2[] = "\xE6\x84\x9F\xE8\xAC\x9D"; //感謝
    const char str3[] = "\xE6\x84\x9B";             //愛
    const char str40[] = "\xE6\x84\x9F";            //感
    const char str41[] = "\xE6\x84\x9F\xE8\xAC\x9D\xE3\x81\x99\xE3\x82\x8B"; //感謝する
    tmp.push_back(str1);
    tmp.push_back(str2);
    tmp.push_back(str3);

    ncva::Trie mytrie(new ncva::UxTrie(NULL));
    mytrie.build(tmp);
    mytrie.save(tempname.c_str());


    ncva::Trie mytrie2(new ncva::UxTrie(tempname.c_str()));
    const ncva::ID_t id1 = mytrie2.getID(str1);
    const ncva::ID_t id2 = mytrie2.getID(str2);
    const ncva::ID_t id3 = mytrie2.getID(str3);
    const ncva::ID_t id40 = mytrie2.getID(str40);
    const ncva::ID_t id41 = mytrie2.getID(str41);

    ASSERT_NE(id1, id2);
    ASSERT_NE(id1, id3);
    ASSERT_NE(id2, id3);
    ASSERT_NE(id1, id40);
    ASSERT_NE(id2, id40);
    ASSERT_NE(id3, id40);
    ASSERT_EQ(id40, id41);

    const std::string trie_str1 = mytrie2.getKey(id1);
    const std::string trie_str2 = mytrie2.getKey(id2);
    const std::string trie_str3 = mytrie2.getKey(id3);
    ASSERT_EQ(str1, trie_str1);
    ASSERT_EQ(str2, trie_str2);
    ASSERT_EQ(str3, trie_str3);

    ASSERT_EQ((ncva::ID_t) 3, mytrie2.size());


    const std::vector<ncva::ID_t> vec_id1 = mytrie2.getIDs(str1);
    const std::vector<ncva::ID_t> vec_id2 = mytrie2.getIDs(str2);
    const std::vector<ncva::ID_t> vec_id3 = mytrie2.getIDs(str3);
    const std::vector<ncva::ID_t> vec_id40 = mytrie2.getIDs(str40);
    const std::vector<ncva::ID_t> vec_id41 = mytrie2.getIDs(str41);
    ASSERT_EQ((size_t) 1, vec_id1.size() );
    ASSERT_EQ((size_t) 1, vec_id2.size() );
    ASSERT_EQ((size_t) 2, vec_id3.size() ); //愛, 愛情
    ASSERT_EQ((size_t) 1, vec_id40.size()); //感謝
    ASSERT_EQ((size_t) 0, vec_id41.size());

    remove(tempname.c_str());
}


