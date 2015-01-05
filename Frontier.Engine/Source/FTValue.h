#pragma once

#include "FTObject.h"

template <typename T>
class FTValue : public FTObject {
private:
	T Data;
	std::hash<T> Hasher;
public:

	explicit FTValue(const T& value) : Data(value) {

	}

	virtual bool IsEqual(const FTObject* a) const {
		const FTValue<T>* val = static_cast<const FTValue<T>*>(a);
		return (val->Get()) == (this->Get());
	}

	const T& Get() const {
		return Data;
	}

	void Set(const T& value) {
		Data = value;
	}

	virtual size_t Hash() const {
		return Hasher(Data);
	}
};
