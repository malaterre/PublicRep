%module(docstring="demo") demo

%{
#include "myvector.h"
%}

%include "stdint.i"
%include "std_vector.i"
%template() std::vector<int>;
%include "myvector.h"
