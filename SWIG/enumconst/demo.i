%module(docstring="demo") demo

%{
#include "myenum.h"
#include "myenum2.h"
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

// Case 1
%include "enumtypesafe.swg" // optional as typesafe enums are the default
//%javaconst(1); // compilation error with swig 2.0.4
%include "myenum.h"

// Case 2
%include "enums.swg"
%typemap(javain) enum SWIGTYPE "$javainput.ordinal()"
%typemap(javaout) enum SWIGTYPE {
    return $javaclassname.class.getEnumConstants()[$jnicall];
  }
%typemap(javabody) enum SWIGTYPE ""
%rename(GetType) myenum2::operator TheType () const;
%include "myenum2.h"
%extend myenum2
{
%typemap(javacode) myenum2
%{
  // For some reason the default equals operator is bogus, provide one ourself
  public boolean equals(Object obj)
    {
    TheType type = (TheType)obj;
    if( type == GetType() )
      {
      return true;
      }
    return false;
    }
%}
};
