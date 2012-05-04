%module(docstring="demo") demo

%{
#include "myfile.h"
%}

%include "stdint.i"
%include "std_vector.i"
%template() std::vector<int>;
%include "myfile.h"
