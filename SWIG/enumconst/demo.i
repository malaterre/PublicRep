%module(docstring="demo") demo

%{
#include "myenum.h"
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

%include "enumtypesafe.swg" // optional as typesafe enums are the default
%javaconst(1);

%include "myenum.h"
