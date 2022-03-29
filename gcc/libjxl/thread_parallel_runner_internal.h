#ifndef LIB_THREADS_THREAD_PARALLEL_RUNNER_INTERNAL_H_
#define LIB_THREADS_THREAD_PARALLEL_RUNNER_INTERNAL_H_

#include <cstddef>
#include <cstdint>

#include <thread>

namespace jpegxl {

class ThreadParallelRunner {
 public:
  static JxlParallelRetCode Runner(void* runner_opaque, void* jpegxl_opaque,
                                   JxlParallelRunInit init,
                                   JxlParallelRunFunction func,
                                   uint32_t start_range, uint32_t end_range);

  explicit ThreadParallelRunner(
      int num_worker_threads = std::thread::hardware_concurrency());

  ~ThreadParallelRunner();

  size_t NumWorkerThreads() const { return 0; }

  size_t NumThreads() const { return 0; }

  template <class Func>
  void RunOnEachThread(const Func& func) {
  }
};

}  // namespace jpegxl

#endif  // LIB_THREADS_THREAD_PARALLEL_RUNNER_INTERNAL_H_
