#pragma once

#include "TTag.h"

namespace detail {
    template<typename T>
    struct has_serialize {
        struct dummy { /* something */ };

        template<typename C, typename P>
        static auto test(P *p) -> decltype(std::declval<C>().serialize(*p), std::true_type());

        template<typename, typename>
        static std::false_type test(...);

        typedef decltype(test<T, dummy>(nullptr)) type;
        static const bool value = std::is_same<std::true_type, decltype(test<T, dummy>(nullptr))>::value;
    };
}

template<typename Archiver, typename T>
struct Serializer {
    static_assert(detail::has_serialize<T>::value,
                  "Doesn't implement serialize - either add serialize member function of provide Serializer specialization");

    static void serialize(Archiver &a, T &val) {
        val.serialize(a);
    }
};


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
        Serializer<OutputSerializer, T>::serialize(*this, value);
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
        Serializer<InputSerializer, T>::serialize(*this, value);
    }
};
