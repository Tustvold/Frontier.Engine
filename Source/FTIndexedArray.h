#pragma once
/*#include "FTObject.h"

// A fixed size array supporting insertion and deletion
// It performs no range checks
template <typename T>
class FTIndexedArray : public FTObject {
public:

	FTIndexedArray(const T* data, size_t size): write_index_(size), max_size_(size), data_(new T[size]) {
		for (int i = 0; i < size; i++)
			data_[i] = data[i];
	}

	explicit FTIndexedArray(size_t size) : write_index_(0), max_size_(size), data_(new T[size]) {
	}

	~FTIndexedArray() {
		delete[] data_;
	}

	T& get(size_t index) const {
		return data_[index];
	}

	void set(size_t index, const T& value) {
		data_[index] = value;
	}

	void append(const T& value) {
		data_[write_index_] = value;
		write_index_++;
	}

	const T* getData() const {
		return data_;
	}

	size_t getSize() const {
		return write_index_;
	}

private:
	size_t write_index_;
	size_t max_size_;

	T* data_;
};
*/