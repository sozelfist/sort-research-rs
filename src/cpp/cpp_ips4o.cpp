#include "thirdparty/ips4o/ips4o.hpp"

#include <stdexcept>

#include <stdint.h>

// ips4o is implemented in a way that requires that T implements a by ref copy
// constructor. That's incompatible with move only types such as FFIStringCpp.
#define SORT_INCOMPATIBLE_WITH_SEMANTIC_CPP_TYPE

#include "shared.h"

template <typename T, typename F>
uint32_t sort_by_impl(T* data, size_t len, F cmp_fn, uint8_t* ctx) noexcept {
    try {
        ips4o::sort(data, data + len, make_compare_fn<T>(cmp_fn, ctx));
    } catch (...) {
        return 1;
    }

    return 0;
}

extern "C" {
// --- i32 ---

void ips4o_unstable_i32(int32_t* data, size_t len) {
    ips4o::sort(data, data + len);
}

uint32_t ips4o_unstable_i32_by(int32_t* data,
                               size_t len,
                               CompResult (*cmp_fn)(const int32_t&, const int32_t&, uint8_t*),
                               uint8_t* ctx) {
    return sort_by_impl(data, len, cmp_fn, ctx);
}

// --- u64 ---

void ips4o_unstable_u64(uint64_t* data, size_t len) {
    ips4o::sort(data, data + len);
}

uint32_t ips4o_unstable_u64_by(uint64_t* data,
                               size_t len,
                               CompResult (*cmp_fn)(const uint64_t&, const uint64_t&, uint8_t*),
                               uint8_t* ctx) {
    return sort_by_impl(data, len, cmp_fn, ctx);
}

// --- ffi_string ---

void ips4o_unstable_ffi_string(FFIString* data, size_t len) {
    ips4o::sort(reinterpret_cast<FFIStringCpp*>(data), reinterpret_cast<FFIStringCpp*>(data) + len);
}

uint32_t ips4o_unstable_ffi_string_by(FFIString* data,
                                      size_t len,
                                      CompResult (*cmp_fn)(const FFIString&,
                                                           const FFIString&,
                                                           uint8_t*),
                                      uint8_t* ctx) {
    return sort_by_impl(reinterpret_cast<FFIStringCpp*>(data), len, cmp_fn, ctx);
}

// --- f128 ---

void ips4o_unstable_f128(F128* data, size_t len) {
    ips4o::sort(reinterpret_cast<F128Cpp*>(data), reinterpret_cast<F128Cpp*>(data) + len);
}

uint32_t ips4o_unstable_f128_by(F128* data,
                                size_t len,
                                CompResult (*cmp_fn)(const F128&, const F128&, uint8_t*),
                                uint8_t* ctx) {
    return sort_by_impl(reinterpret_cast<F128Cpp*>(data), len, cmp_fn, ctx);
}

// --- 1k ---

void ips4o_unstable_1k(FFIOneKibiByte* data, size_t len) {
    ips4o::sort(reinterpret_cast<FFIOneKiloByteCpp*>(data),
                reinterpret_cast<FFIOneKiloByteCpp*>(data) + len);
}

uint32_t ips4o_unstable_1k_by(FFIOneKibiByte* data,
                              size_t len,
                              CompResult (*cmp_fn)(const FFIOneKibiByte&,
                                                   const FFIOneKibiByte&,
                                                   uint8_t*),
                              uint8_t* ctx) {
    return sort_by_impl(reinterpret_cast<FFIOneKiloByteCpp*>(data), len, cmp_fn, ctx);
}
}  // extern "C"
