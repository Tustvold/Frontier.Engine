#pragma once

#include "FTObject.h"
#include <vector>
#include <algorithm>

// Reference counted std::vector
// Will also retain and release FTObject appropriately
template <typename Type, typename A = void>
class FTArray : public FTObject {

};

// Implementation for when storing FTObject's
template <typename Type>
class FTArray<Type, typename std::enable_if<std::is_base_of<FTObject, Type>::value>::type> : public FTObject {
public:

	typedef typename std::vector<Type*>::const_iterator Iterator;

	FTArray() {
	}

	explicit FTArray(int capacity) {
		data_.reserve(capacity);
	}

	~FTArray() {
		clear();
	}

	void add(Type* a, bool retain = true) {
		FTObject* element = a;
		if (retain)
			element->retain();
		data_.push_back(a);
	}

	Type* objectAtIndex(int i) {
		return data_[i];
	}

	void removeObjectAtIndex(int i) {
		FTObject* a = *(data_.begin() + i);
		data_.erase(data_.begin() + i);
		a->release();
	}

	int indexOfObject(Type* a) {
		Iterator it = std::find_if(data_.begin(), data_.end(), [a](const FTObject* m) -> bool {
			                           return m->isEqual(a);
		                           });
		if (it == data_.end()) {
			FTLogWarn("Couldn't find element in array");
			return -1;
		}

		return it - data_.begin();
	}

	void removeObject(Type* a) {
		Iterator it = std::find_if(data_.begin(), data_.end(), [a](const FTObject* m) -> bool {
			                           return m->isEqual(a);
		                           });
		if (it == data_.end()) {
			FTLogWarn("Couldn't find element to remove");
			return;
		}
		FTObject* b = *it;
		data_.erase(it);
		b->release();
	}

	bool containsObject(Type* a) {
		Iterator it = std::find_if(data_.begin(), data_.end(), [a](const FTObject* m) -> bool {
			                           return m->isEqual(a);
		                           });
		return it != data_.end();
	}

	void removeObjectsInRange(Iterator start, Iterator end) {
		for (Iterator it = start; it != end; ++it) {
			FTObject* obj = *it;
			obj->release();
		}
		data_.erase(start, end);
	}

	void clear() {
		removeObjectsInRange(data_.begin(), data_.end());
	}

	void removeObjectsInRange(int startIndex, int endIndex) {
		removeObjectsInRange(data_.begin() + startIndex, data_.begin() + endIndex);
	}

	size_t size() {
		return data_.size();
	}

	const Type** getData() {
		return data_.data();
	}

	Iterator begin() {
		return data_.begin();
	}

	Iterator end() {
		return data_.end();
	}

private:
	std::vector<Type*> data_;
};

template <typename Type>
class FTArray<Type, typename std::enable_if<!std::is_base_of<FTObject, Type>::value>::type> : public FTObject {
public:

	typedef typename std::vector<Type>::const_iterator Iterator;

	FTArray() {
	}

	explicit FTArray(int capacity) {
		data_.reserve(capacity);
	}

	~FTArray() {
		clear();
	}

	void add(const Type& a) {
		data_.push_back(a);
	}

	const Type& objectAtIndex(int i) {
		return data_[i];
	}

	void removeObjectAtIndex(int i) {
		data_.erase(data_.begin() + i);
	}

	int indexOfObject(const Type& a) {
		Iterator it = std::find_if(data_.begin(), data_.end(), [a](const Type& m) -> bool {
			                           return m == a;
		                           });
		if (it == data_.end()) {
			FTLogWarn("Couldn't find element in array");
			return -1;
		}

		return it - data_.begin();
	}

	void removeObject(const Type& a) {
		Iterator it = std::find_if(data_.begin(), data_.end(), [a](const Type& m) -> bool {
			                           return m == a;
		                           });
		if (it == data_.end()) {
			FTLogWarn("Couldn't find element to remove");
			return;
		}
		data_.erase(it);
	}

	bool containsObject(const Type& a) {
		Iterator it = std::find_if(data_.begin(), data_.end(), [a](const Type& m) -> bool {
			                           return m == a;
		                           });
		return it != data_.end();
	}

	void removeObjectsInRange(Iterator start, Iterator end) {
		data_.erase(start, end);
	}

	void clear() {
		removeObjectsInRange(data_.begin(), data_.end());
	}

	void removeObjectsInRange(int startIndex, int endIndex) {
		removeObjectsInRange(data_.begin() + startIndex, data_.begin() + endIndex);
	}

	size_t size() {
		return data_.size();
	}

	const Type* getData() {
		return data_.data();
	}

	Iterator begin() {
		return data_.begin();
	}

	Iterator end() {
		return data_.end();
	}

private:
	std::vector<Type> data_;
};
