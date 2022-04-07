#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include <cassert>

template <typename T> static inline int Round(T x) { return (int)(x + 0.5); }

template <typename T> struct S {
  static inline T Clamp(T v) {
    assert(std::numeric_limits<T>::min() == 0);
    return v < 0 ? 0
                 : (v > std::numeric_limits<T>::max()
                        ? std::numeric_limits<T>::max()
                        : v);
  }
};

template <> struct S<float> {
  static inline float Clamp(float v) { return v < 0. ? 0 : (v > 1.0 ? 1.0 : v); }
};

template <typename T>
static void RGB2YBR(T ybr[3], const T rgb[3], unsigned short storedbits) {
  // Implementation details, since the equations from:
  // http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.3.html#sect_C.7.6.3.1.2
  // are rounded to the 4th decimal precision, prefer the exact equation from
  // the original document at: CCIR Recommendation 601-2, also found in T.871
  // (Section §7, page 4)
  const double R = rgb[0];
  const double G = rgb[1];
  const double B = rgb[2];
  assert(storedbits <= sizeof(T) * 8);
  const unsigned int halffullscale = 1u << (storedbits - 1);
  const double Yd = 0.299 * R + 0.587 * G + 0.114 * B;
  const double CBd1 = (-0.299 * R - 0.587 * G + 0.886 * B) / 1.772;
  const double CRd1 = (0.701 * R - 0.587 * G - 0.114 * B) / 1.402;

#if 0
  const double CBd = CBd1 + halffullscale;
  const double CRd = CRd1 + halffullscale;
#else
  const double CBd = CBd1 + 0;
  const double CRd = CRd1 + 0;
#endif

  const int Y = Round(Yd);
  const int CB = Round(CBd);
  const int CR = Round(CRd);
#if 0
  ybr[0] = S<T>::Clamp(Y);
  ybr[1] = S<T>::Clamp(CB);
  ybr[2] = S<T>::Clamp(CR);
#else
  ybr[0] = S<T>::Clamp(Yd);
  ybr[1] = S<T>::Clamp(CBd);
  ybr[2] = S<T>::Clamp(CRd);
#endif
}

template <typename T>
void YBR2RGB(T rgb[3], const T ybr[3], unsigned short storedbits) {
  const double Y = ybr[0];
  const double Cb = ybr[1];
  const double Cr = ybr[2];
  assert(storedbits <= sizeof(T) * 8);
  const unsigned int halffullscale = 1u << (storedbits - 1);
  const int R = Round(Y + 1.402 * (Cr - halffullscale));
  const int G = Round(Y - (0.114 * 1.772 * (Cb - halffullscale) +
                           0.299 * 1.402 * (Cr - halffullscale)) /
                              0.587);
  const int B = Round(Y + 1.772 * (Cb - halffullscale));
  rgb[0] = S<T>::Clamp(R);
  rgb[1] = S<T>::Clamp(G);
  rgb[2] = S<T>::Clamp(B);
}

// return square dist
template <typename T> static double Dist2(T v1[3], const T v2[3]) {
  double ret = 0;
  for (int i = 0; i < 3; ++i)
    ret += (v1[i] - v2[i]) * (v1[i] - v2[i]);
  return ret;
}

int main(int argc, char *argv[]) {
  const char *filename = argv[1];
  std::ifstream is(filename, std::ios::binary);
  std::ofstream os("out.pfm", std::ios::binary);
  os << "Pf\n";
  std::string str;
  std::getline(is, str);
  std::cerr << str << std::endl;
  if (str != "PF" )
    return 1;
  unsigned int ncomps = str == "PF" ? 3u : 1u;
  std::getline(is, str);
  std::cerr << str << std::endl;
  long width, height;
  {
    std::istringstream iss(str);
    iss >> width;
    iss >> height;
  }
  os << width << " " << height << '\n';
  os << "-1.0\n";
  std::getline(is, str);
  std::cerr << str << std::endl;
  size_t nfloats = width * height * ncomps;
  std::cerr << nfloats << std::endl;
  float fmin, fmax;
  fmin = std::numeric_limits<float>::max();
  fmax = std::numeric_limits<float>::lowest(); // min
  double count = 0;
  if (nfloats % 3)
    return 1;
  size_t npixels = nfloats / 3;
  double d = 0;
  for (size_t i = 0; i < npixels; ++i) {
    float rgb[3] = {};
    float rgb2[3] = {};
    float ybr[3] = {};
    is.read((char *)rgb, sizeof rgb);
    RGB2YBR(ybr, rgb, 32);
    YBR2RGB(rgb2, ybr, 32);
    const double dist = Dist2(rgb, rgb2);
    d += dist;
    os.write((char*)ybr, sizeof(float));
  }
  std::cerr << d << std::endl;
  std::cerr << d / npixels << std::endl;
  return 1;
}
