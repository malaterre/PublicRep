#ifndef LIB_JXL_BASE_DATA_PARALLEL_H_
#define LIB_JXL_BASE_DATA_PARALLEL_H_

#include <cstddef>
#include <cstdint>

#include "parallel_runner.h"

namespace jxl {

class ThreadPool {
 public:
  ThreadPool(JxlParallelRunner runner, void* runner_opaque)
      : runner_(runner ? runner : &ThreadPool::SequentialRunnerStatic),
        runner_opaque_(runner ? runner_opaque : static_cast<void*>(this)) {}

  template <class InitFunc, class DataFunc>
  bool Run(uint32_t begin, uint32_t end, const InitFunc& init_func,
             const DataFunc& data_func, const char* caller = "") {
    if (begin == end) return true;
    RunCallState<InitFunc, DataFunc> call_state(init_func, data_func);
    return (*runner_)(runner_opaque_, static_cast<void*>(&call_state),
                      &call_state.CallInitFunc, &call_state.CallDataFunc, begin,
                      end) == 0;
  }

  static bool NoInit(size_t num_threads) { return true; }

 private:
  template <class InitFunc, class DataFunc>
  class RunCallState final {
   public:
    RunCallState(const InitFunc& init_func, const DataFunc& data_func)
        : init_func_(init_func), data_func_(data_func) {}

    static int CallInitFunc(void* jpegxl_opaque, size_t num_threads) {
      const auto* self =
          static_cast<RunCallState<InitFunc, DataFunc>*>(jpegxl_opaque);
      return self->init_func_(num_threads) ? 0 : -1;
    }

    static void CallDataFunc(void* jpegxl_opaque, uint32_t value,
                             size_t thread_id) {
      const auto* self =
          static_cast<RunCallState<InitFunc, DataFunc>*>(jpegxl_opaque);
      self->data_func_(value, thread_id);
    }

   private:
    const InitFunc& init_func_;
    const DataFunc& data_func_;
  };

  static JxlParallelRetCode SequentialRunnerStatic(
      void* runner_opaque, void* jpegxl_opaque, JxlParallelRunInit init,
      JxlParallelRunFunction func, uint32_t start_range, uint32_t end_range);

  const JxlParallelRunner runner_;
  void* const runner_opaque_;
};

template <class InitFunc, class DataFunc>
bool /*Status*/ RunOnPool(ThreadPool* pool, const uint32_t begin, const uint32_t end,
                 const InitFunc& init_func, const DataFunc& data_func,
                 const char* caller) {
  if (pool == nullptr) {
    ThreadPool default_pool(nullptr, nullptr);
    return default_pool.Run(begin, end, init_func, data_func, caller);
  } else {
    return pool->Run(begin, end, init_func, data_func, caller);
  }
}

}  // namespace jxl

#endif  // LIB_JXL_BASE_DATA_PARALLEL_H_
