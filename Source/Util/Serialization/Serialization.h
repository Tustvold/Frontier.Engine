#pragma once

#include "TTag.h"

class OutputSerializer {
    std::ostream *ostream;
public:
    OutputSerializer(std::ostream *ostream) : ostream(ostream) {

    }

    template<typename T, typename std::enable_if<detail::TagID<T>::value, int>::type = 0>
    void operator&(const T &value) {
        detail::TagID<T>::writeID(ostream);
        detail::TTag<T>::writeData(value, ostream);
    }

    template<typename T, typename std::enable_if<!detail::TagID<T>::value, int>::type = 0>
    void operator&(T &value) {
        value.serialize(*this);
    }
};

class InputSerializer {
    std::istream *istream;
public:
    InputSerializer(std::istream *istream) : istream(istream) {

    }

    template<typename T, typename std::enable_if<detail::TagID<T>::value, int>::type = 0>
    void operator&(T &value) {
        detail::TagID<T>::readID(istream);
        value = detail::TTag<T>::readData(istream);
    }

    template<typename T, typename std::enable_if<!detail::TagID<T>::value, int>::type = 0>
    void operator&(T &value) {
        value.serialize(*this);
    }
};
