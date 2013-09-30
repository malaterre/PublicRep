%module(directors="1") demo

%feature("director");      
//%include "cpointer.i"
//%pointer_functions(base,basep)

%{
#include "virt.h"
%}

%ignore base::create_concrete(bool b);
%include "virt.h"

%{
base * create_concrete_for_php(bool b = true) {
  return base::create_concrete(b);
}
%}
base * create_concrete_for_php(bool b = true);
