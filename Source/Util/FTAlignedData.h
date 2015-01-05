#pragma once
#include <algorithm>

// A wrapper around T which ensures 16-bit alignment on the heap
template <typename T>
class FTAlignedData {
public:
	FTAlignedData() {
		void* ptr = _aligned_malloc(sizeof(T), 16);
		aligned_data_ = new(ptr)T();
		//*aligned_data_ = T();
	}

	~FTAlignedData() {
		aligned_data_->~T();
		_aligned_free(aligned_data_);
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
