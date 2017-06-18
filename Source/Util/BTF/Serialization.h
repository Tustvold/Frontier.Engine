#pragma once

#include "TTag.h"

class OutputSerializer {
    Buffer* buffer;
public:
    OutputSerializer(Buffer* buffer) : buffer(buffer) {

    }

    template<typename T>
    void operator&(const T &value) {
        Serialization::TagID<T>::writeID(buffer);
        Serialization::TTag<T>::writeData(value, buffer);
    }
};

class InputSerializer {
    Buffer* buffer;
public:
    InputSerializer(Buffer* buffer) : buffer(buffer) {

    }

    template<typename T>
    void operator&(T &value) {
        Serialization::TagID<T>::readID(buffer);
        value = Serialization::TTag<T>::readData(buffer);
    }
};
