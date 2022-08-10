#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
int main(int argc, char *argv[]) {
  const char *filename = argv[1];
  std::ifstream is(filename, std::ios::binary);
  std::string str;
  std::getline(is, str);
  std::cerr << str << std::endl;
  if (str != "PF" && str != "Pf")
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
  std::getline(is, str);
  std::cerr << str << std::endl;
  {
    double endian;
    std::istringstream iss(str);
    iss >> endian;
    if (endian > 0)
      return 1;
  }
  size_t nfloats = width * height * ncomps;
  std::cerr << nfloats << std::endl;
  float fmin, fmax;
  fmin = std::numeric_limits<float>::max();
  fmax = std::numeric_limits<float>::lowest(); // min
  double count = 0;
  for (size_t i = 0; i < nfloats; ++i) {
    float f = -1;
    is.read((char *)&f, sizeof f);
    fmin = std::min(fmin, f);
    fmax = std::max(fmax, f);
    count += f;
  }
  std::cerr << "min/max:" << fmin << " " << fmax << std::endl;
  std::cerr << count << std::endl;
  std::cerr << count / nfloats << std::endl;
  return 1;
}
