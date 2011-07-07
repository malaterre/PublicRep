%module(docstring="demo") demo

%{
#include "myfile.h"
%}

%pragma(java) jniclasscode=%{
 static {
   try {
       System.loadLibrary("demo");
   } catch (UnsatisfiedLinkError e) {
     System.err.println("Native code library failed to load. \n" + e);
     System.exit(1);
   }
 }
%}

%include "myfile.h"
