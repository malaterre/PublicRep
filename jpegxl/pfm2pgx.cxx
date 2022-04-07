#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include <cassert>

int main(int argc, char *argv[]) {
  const char *filename = argv[1];
  const int nbits = atoi(argv[2]);
  std::cerr << nbits << std::endl;
  std::ifstream is(filename, std::ios::binary);
  std::ostringstream oss;
  oss << "out" << nbits << ".pgx";
  std::ofstream os(oss.str().c_str(), std::ios::binary);
  std::string str;
  std::getline(is, str);
  std::cerr << str << std::endl;
  if (str != "Pf")
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
  // PG ML + 16 512 512
  os << "PG LM + " << nbits;
  os << " " << width << " " << height << '\n';
  const unsigned long mult = (1ull << nbits) - 1;
  std::cout << "mult:" << mult << std::endl;
  assert(mult <= std::numeric_limits<unsigned int>::max());
  for (size_t i = 0; i < nfloats; ++i) {
    float f = -1;
    is.read((char *)&f, sizeof f);
    fmin = std::min(fmin, f);
    fmax = std::max(fmax, f);
    count += f;
    double d = f;
    if (nbits <= 16) {
      unsigned int ui = d * mult;
      assert(ui >= 0 && ui <= mult);
      unsigned short u = ui;
      os.write((char *)&u, sizeof u);
    } else if (nbits <= 32) {
      unsigned long ul = d * mult;
      assert(ul >= 0 && ul <= mult);
      unsigned int u = ul;
      os.write((char *)&u, sizeof u);
    }
  }
  std::cerr << fmin << " " << fmax << std::endl;
  std::cerr << count << std::endl;
  std::cerr << count / nfloats << std::endl;
  return 1;
}
