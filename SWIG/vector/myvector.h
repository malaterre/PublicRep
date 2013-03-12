#include <vector>

#ifdef _WIN32
  #if defined(thelib_EXPORTS) || defined(demo_EXPORTS)
    #define MY_EXPORT __declspec( dllexport )
  #else
    #define MY_EXPORT __declspec( dllimport )
  #endif
#else
  #define MY_EXPORT
#endif

class MY_EXPORT my_vector
{
 std::vector<int> I;
public:
 typedef std::vector<int>::size_type SizeType; // not working
 //typedef size_t SizeType; // nope...
 //typedef int SizeType; // yay !

 SizeType Count() const;

 std::vector<int> const & GetI() const;
};
