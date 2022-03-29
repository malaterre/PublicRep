#ifndef LIB_JXL_BASE_THREAD_POOL_INTERNAL_H_
#define LIB_JXL_BASE_THREAD_POOL_INTERNAL_H_

#include <thread>

#include "data_parallel.h"
#include "thread_parallel_runner_internal.h"

namespace jxl {

class ThreadPoolInternal : public ThreadPool {
 public:
  explicit ThreadPoolInternal(
      int num_worker_threads = std::thread::hardware_concurrency())
      : ThreadPool(&jpegxl::ThreadParallelRunner::Runner,
                   static_cast<void*>(&runner_)),
        runner_(num_worker_threads) {}

  template <class Func>
  void RunOnEachThread(const Func& func) {
    runner_.RunOnEachThread(func);
  }

 private:
  jpegxl::ThreadParallelRunner runner_;
};

}  // namespace jxl

#endif  // LIB_JXL_BASE_THREAD_POOL_INTERNAL_H_
