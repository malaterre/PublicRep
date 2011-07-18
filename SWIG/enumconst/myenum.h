#ifdef _WIN32
  #if defined(thelib_EXPORTS) || defined(demo_EXPORTS)
    #define MY_EXPORT __declspec( dllexport )
  #else
    #define MY_EXPORT __declspec( dllimport )
  #endif
#else
  #define MY_EXPORT
#endif

class MY_EXPORT myenum
{
public:
  typedef enum {
    VM0 = 0,
    VM1 = 1,
    VM2 = 2,
    VM3 = 4,
    VM4 = 8,
    VM5 = 16,
    VM6 = 32,
    VM8 = 64,
    VM9 = 128,
    VM10 = 256,
    VM12 = 512, //1024,
    VM16 = 1024, //2048,
    VM18 = 2048, //4096,
    VM24 = 4096, //8192,
    VM28 = 8192, //16384,
    VM32 = 16384, //32768,
    VM35 = 32768, //65536,
    VM99 = 65536, //131072,
    VM256 = 131072, //262144,
    VM1_2  = VM1 | VM2,
    VM1_3  = VM1 | VM2 | VM3,
    VM1_4  = VM1 | VM2 | VM3 | VM4,
    VM1_5  = VM1 | VM2 | VM3 | VM4 | VM5,
    VM1_8  = VM1 | VM2 | VM3 | VM4 | VM5 | VM6 | VM8,
    VM1_32 = VM1 | VM2 | VM3 | VM4 | VM5 | VM6 | VM8 | VM9 | VM16 | VM24 | VM32,
    VM1_99 = VM1 | VM2 | VM3 | VM4 | VM5 | VM6 | VM8 | VM9 | VM16 | VM24 | VM32 | VM99,
    VM1_n  = VM1 | VM2 | VM3 | VM4 | VM5 | VM6 | VM8 | VM9 | VM16 | VM24 | VM32 | VM99 | VM256,
    VM2_2n =       VM2       | VM4       | VM6 | VM8       | VM16 | VM24 | VM32        | VM256,
    VM2_n  =       VM2 | VM3 | VM4 | VM5 | VM6 | VM8 | VM9 | VM16 | VM24 | VM32 | VM99 | VM256,
    VM3_4  =             VM3 | VM4,
    VM3_3n =             VM3 |             VM6       | VM9        | VM24        | VM99 | VM256,
    VM3_n  =             VM3 | VM4 | VM5 | VM6 | VM8 | VM9 | VM16 | VM24 | VM32 | VM99 | VM256,
    VM4_4n =                   VM4                         | VM16 | VM24 | VM32        | VM256,
    VM6_6n =                               VM6             | VM12 | VM18 | VM24               ,
    VM7_7n,
    VM30_30n,
    VM47_47n,
    VM_END = VM1_n + 1  // Custom tag to count number of entry
  } VMType;

  operator VMType () const { return VMField; }

  myenum(VMType type = VM_END);

private:
  VMType VMField;
};
