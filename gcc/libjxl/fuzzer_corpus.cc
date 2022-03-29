#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include <vector>
#include <thread>

#include "thread_pool_internal.h"
namespace jxl {
constexpr unsigned char kContainerHeader[] = {
    0,   0,   0, 0xc, 'J',  'X', 'L', ' ', 0xd, 0xa, 0x87,
    0xa, 0,   0, 0,   0x14, 'f', 't', 'y', 'p', 'j', 'x',
    'l', ' ', 0, 0,   0,    0,   'j', 'x', 'l', ' '};
}

namespace {

struct ImageSpec {
  uint64_t width = 256;
  uint64_t height = 256;
  uint64_t num_channels = 3;
  uint64_t bit_depth = 8;
  uint64_t alpha_bit_depth = 8;
  uint64_t num_frames = 1;
};

bool GenerateFile(const char* output_dir, const ImageSpec& spec,
                  bool regenerate, bool quiet) {
  for (uint32_t frame = 0; frame < spec.num_frames; frame++) {
    const size_t bytes_per_sample = 1;
    const size_t bytes_per_pixel = bytes_per_sample * 3;
    const size_t row_size = spec.width * bytes_per_pixel;
    std::vector<uint8_t> img_data(row_size * spec.height, 0);
  }

    std::vector<uint8_t> header;
    header.insert(header.end(), jxl::kContainerHeader,
                  jxl::kContainerHeader + sizeof(jxl::kContainerHeader));

  return true;
}

}  // namespace

int main(int argc, const char** argv) {
  const char* dest_dir = nullptr;
  bool regenerate = false;
  bool quiet = false;
  int num_threads = std::thread::hardware_concurrency();

  for (uint32_t fuzzer_friendly = 0; fuzzer_friendly < 2; ++fuzzer_friendly) {
    std::vector<ImageSpec> specs;

    jxl::ThreadPoolInternal pool{num_threads};
    if (!RunOnPool(
            &pool, 0, specs.size(), jxl::ThreadPool::NoInit,
            [&specs, dest_dir, regenerate, quiet](const uint32_t task,
                                                  size_t /* thread */) {
              const ImageSpec& spec = specs[task];
              GenerateFile(dest_dir, spec, regenerate, quiet);
            },
            "FuzzerCorpus")) {
      return 1;
    }
  }
  return 0;
}
