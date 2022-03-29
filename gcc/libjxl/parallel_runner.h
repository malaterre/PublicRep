#ifndef JXL_PARALLEL_RUNNER_H_
#define JXL_PARALLEL_RUNNER_H_

#include <cstddef>
#include <cstdint>

extern "C" {

typedef int JxlParallelRetCode;

typedef JxlParallelRetCode (*JxlParallelRunInit)(void* jpegxl_opaque,
                                                 size_t num_threads);

typedef void (*JxlParallelRunFunction)(void* jpegxl_opaque, uint32_t value,
                                       size_t thread_id);

typedef JxlParallelRetCode (*JxlParallelRunner)(
    void* runner_opaque, void* jpegxl_opaque, JxlParallelRunInit init,
    JxlParallelRunFunction func, uint32_t start_range, uint32_t end_range);
}

#endif /* JXL_PARALLEL_RUNNER_H_ */
