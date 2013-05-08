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
    const unsigned int get(const char* query) const{
        return $self->getFreq(query);
    }

    const unsigned long int getTotal() const{
        return $self->getSum();
    }

}

