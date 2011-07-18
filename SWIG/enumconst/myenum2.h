#ifdef _WIN32
  #if defined(thelib_EXPORTS) || defined(demo_EXPORTS)
    #define MY_EXPORT __declspec( dllexport )
  #else
    #define MY_EXPORT __declspec( dllimport )
  #endif
#else
  #define MY_EXPORT
#endif

class MY_EXPORT myenum2
{
public:
  typedef enum {
    FOO1,
    FOO2,
    FOO3,
    FOO4,
    THE_END
  } TheType;

  operator TheType () const { return TheField; }

  myenum2(TheType type = THE_END);

private:
  TheType TheField;
};
