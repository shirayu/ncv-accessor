%module ncva
%include "std_string.i"
%include "stl.i"
%include "exception.i"
%{
#include "ncva.hpp"
#include "common.hpp"

using namespace ncva;
using namespace std;


%}
%include "ncva.hpp"
%include "common.hpp"

class Ncva;
%extend ncva::Ncva{
    unsigned int get(const char* query){
        return $self->getFreq(query);
    }
}

