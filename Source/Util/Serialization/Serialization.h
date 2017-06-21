#pragma once

#include "TTag.h"

class OutputSerializer {
    ttvfs::File *file;
public:
    OutputSerializer(ttvfs::File *file) : file(file) {

    }

    template<typename T, typename std::enable_if<detail::TagID<T>::value, int>::type = 0>
    void operator&(const T &value) {
        detail::TagID<T>::writeID(file);
        detail::TTag<T>::writeData(value, file);
    }

    template<typename T, typename std::enable_if<!detail::TagID<T>::value, int>::type = 0>
    void operator&(T &value) {
        value.serialize(*this);
    }
};

class InputSerializer {
    ttvfs::File *file;
public:
    InputSerializer(ttvfs::File *file) : file(file) {

    }

    template<typename T, typename std::enable_if<detail::TagID<T>::value, int>::type = 0>
    void operator&(T &value) {
        detail::TagID<T>::readID(file);
        value = detail::TTag<T>::readData(file);
    }

    template<typename T, typename std::enable_if<!detail::TagID<T>::value, int>::type = 0>
    void operator&(T &value) {
        value.serialize(*this);
    }
};
