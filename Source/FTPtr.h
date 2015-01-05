#pragma once

#include "FTObject.h"

template <typename T>
class FTPtr {
public:

	explicit FTPtr(T* obj, bool retain = true) {
		data_ = obj;

		if (retain)
			data_->retain();
	}

	FTPtr() {
		data_ = nullptr;
	}

	~FTPtr() {
		data_->release();
	}

	T& operator*() {
		return *data_;
	}

	T* operator->() {
		return data_;
	}

	FTPtr(const FTPtr& other) {
		data_ = other.data_;
		data_->retain();
	}

	T* get() {
		return data_;
	}

	FTPtr& operator=(const FTPtr& other) {
		if (data_ != nullptr)
			data_->release();
		data_ = other->data_;
		data_->retain();
	}

private:
	T* data_;
};
