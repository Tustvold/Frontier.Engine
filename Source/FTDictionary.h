#pragma once

#include "FTObject.h"
#include <unordered_map>
#include "FTString.h"
#include <type_traits>

template <typename Key>
class FTHasher {

public:
	size_t operator()(const Key* ptr) {
		const FTObject* value = ptr;
		return value->hash();
	}
};

template <typename Key>
class FTComparer {

public:
	bool operator()(const Key* a, const Key* b) {
		const FTObject* obj = a;
		return obj->isEqual(b);
	}
};


// Dictionary class for storing instances of FTObject using either value types or instances of FTObject as the key
// If an FTObject is used as the key it is expected for it to override Hash and isEqual()
// It will retain added FTObjects and release them when they are either removed or the instance of FTDictionary is destroyed
// If a value type is used the 3rd and 4th template arguments can be used to specify a hasher and comparer other than std::hash and std::equal_to
template <typename Key, typename Value, typename Hasher = std::hash<Key>, typename Comparer = std::equal_to<Key>, typename A = void, typename B = void>
class FTDictionary : public FTObject {

};

// Implementation for when Value and Key are both FTObjects
template <typename Key, typename Value, typename Hasher, typename Comparer>
class FTDictionary<Key, Value, Hasher, Comparer, typename std::enable_if<std::is_base_of<FTObject, Key>::value>::type, typename std::enable_if<std::is_base_of<FTObject, Value>::value>::type> : public FTObject {
public:

	typedef typename std::unordered_map<Key*, Value*>::const_iterator Iterator;

	explicit FTDictionary(size_t n = 10) : data_(n, hasher_, comparer_) {

	}

	~FTDictionary() {
		for (Iterator it = begin(); it != end(); ++it) {
			it->first->release();
			it->second->release();
		}
	}

	bool contains(Key* key) {
		return data_.find(key) != data_.end();
	}

	//Throws std::out_of_range if key is not found
	Value* get(Key* value) {
		return data_.at(value);
	}

	void add(Key* key, Value* value, bool retain_key = true, bool retain_value = true) {
		FTAssert(data_.find(key) == data_.end(), "Dictionary already contains object");
		data_[key] = value;
		if (retain_value)
			value->retain();
		if (retain_key)
			key->retain();
	}

	void removeValueForKey(Key* key) {
		data_.erase(data_.find(key));
	}

	void clear() {
		for (Iterator it = begin(); it != end(); ++it) {
			it->second->release();
		}
		data_.clear();
	}

	Iterator begin() {
		return data_.begin();
	}

	Iterator end() {
		return data_.end();
	}

private:

	FTHasher<Key> hasher_;
	FTComparer<Key> comparer_;

	std::unordered_map<Key*, Value*, FTHasher<Key>, FTComparer<Key>> data_;
};

// Implementation for when only Value is an FTObject
template <typename Key, typename Value, typename Hasher, typename Comparer>
class FTDictionary<Key, Value, Hasher, Comparer, typename std::enable_if<!std::is_base_of<FTObject, Key>::value>::type, typename std::enable_if<std::is_base_of<FTObject, Value>::value>::type> : public FTObject {
public:

	typedef typename std::unordered_map<Key, Value*, Hasher, Comparer>::const_iterator Iterator;

	explicit FTDictionary(size_t n = 10) : data_(n, hasher_, comparer_) {

	}

	~FTDictionary() {
		for (Iterator it = begin(); it != end(); ++it) {
			it->second->release();
		}
	}

	bool contains(const Key& key) {
		return data_.find(key) != data_.end();
	}

	// Returns nullptr if not found
	Value* get(const Key& key) {
		Iterator it = data_.find(key);
		if (it == data_.end())
			return nullptr;
		return it->second;
	}

	void add(const Key& key, Value* value, bool retain_value = true) {
		FTAssert(data_.find(key) == data_.end(), "Dictionary already contains object");
		data_[key] = value;
		if (retain_value)
			value->retain();
	}

	void removeValueForKey(const Key& key) {
		data_.erase(data_.find(key));
	}

	void clear() {
		for (Iterator it = begin(); it != end(); ++it) {
			it->second->release();
		}
		data_.clear();
	}

	Iterator begin() {
		return data_.begin();
	}

	Iterator end() {
		return data_.end();
	}
private:

	Hasher hasher_;
	Comparer comparer_;

	std::unordered_map<Key, Value*, Hasher, Comparer> data_;
	//std::hash<Key> hasher_;
};
