%module(directors="1") demo

%feature("director");      

%{
#include "virt.h"
%}

%include "virt.h"
