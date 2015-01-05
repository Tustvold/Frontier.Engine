//
//  FTArray.h
//  Frontier
//
//  Created by Raphael Taylor-Davies on 09/06/2014.
//  Copyright (c) 2014 Subterranean Software. All rights reserved.
//

#pragma once

#include "FTObject.h"
#include <vector>
#include <algorithm>


template <typename Type>
class FTArray : public FTObject {
public:

	typedef typename std::vector<Type*>::const_iterator Iterator;

	FTArray() {
	}

	FTArray(int capacity) : data_(capacity) {

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

	int size() {
		return data_.size();
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
