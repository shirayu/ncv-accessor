/*
 * Copyright (c) Yuta Hayashibe
 * LICENSE : GNU GENERAL PUBLIC LICENSE Version 3
 *
 */

#include <tr1/unordered_map>

#include <stdint.h>

#ifndef HEADER_ad8d275923a44807ad6fd9621b1e83b5
#define HEADER_ad8d275923a44807ad6fd9621b1e83b5


namespace ncva{
    typedef uint32_t FREQUENCY;
    typedef uint64_t FREQUENCY_LONG;
    typedef std::tr1::unordered_map<std::string, FREQUENCY> MAP_FREQUENCY;

    typedef uint64_t ID_t;
    enum {
      NOTFOUND      = 0xFFFFFFFFU,
      LIMIT_DEFAULT = 0xFFFFFFFFU
    };
}


// Following codes are imported from CaboCha developed by Taku Kudo <taku@chasen.org>
// The license is new BSD (3-clause) license.

#include <setjmp.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>


namespace ncva{
//    class die {
//     public:
//      die() {}
//      ~die() {
//        std::cerr << std::endl;
//        exit(-1);
//      }
//      int operator&(std::ostream&) { return 0; }
//    };

//    struct whatlog {
//      std::ostringstream stream_;
//      std::string str_;
//      const char *str() {
//        str_ = stream_.str();
//        return str_.c_str();
//      }
//    };

//    class wlog {
//     public:
//      wlog(whatlog *what) : what_(what) {
//        what_->stream_.clear();
//      }
//      bool operator&(std::ostream &) {
//        return false;
//      }
//     private:
//      whatlog *what_;
//    };
}


#define WHAT what_.stream_

#define CHECK_FALSE(condition) \
 if (condition) {} else  \
   std::cerr <<              \
      __FILE__ << "(" << __LINE__ << ") [" << #condition << "] "


#define CHECK_DIE(condition) \
(condition) ? 0 : die() & std::cerr << __FILE__ << \
"(" << __LINE__ << ") [" << #condition << "] "

#if defined(_WIN32) && !defined(__CYGWIN__)
#include <hash_map>
#include <hash_set>
#if _MSC_VER < 1310 || _MSC_VER >= 1600
using std::hash_map;
#else
using stdext::hash_map;
#endif
#else

#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#if GCC_VERSION >= 40300
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#define hash_map std::tr1::unordered_map
#define hash_set std::tr1::unordered_set
#else
#include <ext/hash_map>
#include <ext/hash_set>
using __gnu_cxx::hash_map;
using __gnu_cxx::hash_set;

#include <string>
namespace __gnu_cxx {
template <>
struct hash<std::string> {
  std::size_t operator()(const std::string &s) const {
    std::size_t result = 0;
    for (std::string::const_iterator it = s.begin(); it != s.end(); ++it) {
      result = (result * 131) + *it;
    }
    return result;
  }
};

template <>
struct hash<uint64> {
  std::size_t operator()(const uint64 s) const {
    return s;
  }
};
}
#endif
#endif
// Above codes are imported from CaboCha developed by Taku Kudo <taku@chasen.org>


#endif
