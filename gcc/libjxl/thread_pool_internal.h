#ifndef LIB_JXL_BASE_THREAD_POOL_INTERNAL_H_
#define LIB_JXL_BASE_THREAD_POOL_INTERNAL_H_

#include <cstddef>
#include <cmath>

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

  ThreadPoolInternal(const ThreadPoolInternal&) = delete;
  ThreadPoolInternal& operator&(const ThreadPoolInternal&) = delete;

  size_t NumThreads() const { return runner_.NumThreads(); }
  size_t NumWorkerThreads() const { return runner_.NumWorkerThreads(); }

  template <class Func>
  void RunOnEachThread(const Func& func) {
    runner_.RunOnEachThread(func);
  }

 private:
  jpegxl::ThreadParallelRunner runner_;
};

}  // namespace jxl

#endif  // LIB_JXL_BASE_THREAD_POOL_INTERNAL_H_
