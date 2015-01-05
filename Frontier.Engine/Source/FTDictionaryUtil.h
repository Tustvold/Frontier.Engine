#pragma once
#include <typeinfo>

class TypeInfoHasher {
public:
	size_t operator()(const std::type_info* data) {
		return data->hash_code();
	}
};

class TypeInfoComparer {

public:
	bool operator()(const std::type_info* a, const std::type_info* b) {
		return (*a) == (*b);
	}
};
