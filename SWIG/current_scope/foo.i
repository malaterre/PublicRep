%module(docstring="demo",directors=1) foo

%{
#include "cov.h"
using namespace foo;
%}

%include "cov.h"
