#include <string>

#ifdef _WIN32
  #if defined(thelib_EXPORTS) || defined(demo_EXPORTS)
    #define MY_EXPORT __declspec( dllexport )
  #else
    #define MY_EXPORT __declspec( dllimport )
  #endif
#else
  #define MY_EXPORT
#endif

class MY_EXPORT myfile
{
public:
  static bool open( const char *filename );
};

std::string read_metadata( const char *filename );
