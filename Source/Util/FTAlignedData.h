#pragma once
#include <algorithm>

// A wrapper around T which ensures 16-bit alignment on the heap
template <typename T>
class FTAlignedData {
public:
    FTAlignedData() {
#if (__STDC_VERSION__ >= 201112L) || _ISOC11_SOURCE
        // if we're C11, use the standard aligned alloc function
        void* ptr = aligned_alloc(16, sizeof(T));
#else
        void* ptr = _aligned_malloc(sizeof(T), 16);
#endif
        aligned_data_ = new(ptr)T();
        //*aligned_data_ = T();
    }

    ~FTAlignedData() {
        aligned_data_->~T();
#if (__STDC_VERSION__ >= 201112L) || _ISOC11_SOURCE
        // if we're C11, use the standard free function since we used
        // aligned_alloc to allocate the data
        free(aligned_data_);
#else
        _aligned_free(aligned_data_);
#endif
    }

    const T& getConstData() const {
        return *aligned_data_;
    }

    const T* getDataPointer() const {
        return aligned_data_;
    }

    T& getData() {
        return *aligned_data_;
    }

    T& operator=(const T& other) {
        return (*aligned_data_) = other;
    }

private:
    T* aligned_data_;
};
