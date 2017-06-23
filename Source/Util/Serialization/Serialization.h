#pragma once

#include "TTag.h"

NS_FT_BEGIN

namespace serialization_detail {
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
    static_assert(serialization_detail::has_serialize<T>::value,
                  "Doesn't implement serialize - either add serialize member function of provide Serializer specialization");

    static void serialize(Archiver &a, T &val) {
        val.serialize(a);
    }
};


class OutputSerializer {
    ttvfs::File *file;
public:
    static const bool is_output = true;
    static const bool is_input = false;

    OutputSerializer(ttvfs::File *file) : file(file) {

    }

    template<typename T, typename std::enable_if<serialization_detail::TagID<T>::value, int>::type = 0>
    void operator&(const T &value) {
        serialization_detail::TagID<T>::writeID(file);
        serialization_detail::TTag<T>::writeData(value, file);
    }

    template<typename T, typename std::enable_if<!serialization_detail::TagID<T>::value, int>::type = 0>
    void operator&(T &value) {
        Serializer<OutputSerializer, T>::serialize(*this, value);
    }

    template<typename T, typename std::enable_if<serialization_detail::TagID<T>::value, int>::type = 0>
    void serializePrimitiveArray(T *value, size_t length) {
        serialization_detail::TagID<T[]>::writeID(file);
        for (size_t i = 0; i < length; i++) {
            serialization_detail::TTag<T>::writeData(value[i], file);
        }
    }
};

class InputSerializer {
    ttvfs::File *file;
public:
    static const bool is_output = false;
    static const bool is_input = true;

    InputSerializer(ttvfs::File *file) : file(file) {

    }

    template<typename T, typename std::enable_if<serialization_detail::TagID<T>::value, int>::type = 0>
    void operator&(T &value) {
        serialization_detail::TagID<T>::readID(file);
        serialization_detail::TTag<T>::readData(value, file);
    }

    template<typename T, typename std::enable_if<!serialization_detail::TagID<T>::value, int>::type = 0>
    void operator&(T &value) {
        Serializer<InputSerializer, T>::serialize(*this, value);
    }

    template<typename T, typename std::enable_if<serialization_detail::TagID<T>::value, int>::type = 0>
    void serializePrimitiveArray(T *value, size_t length) {
        serialization_detail::TagID<T[]>::readID(file);
        for (size_t i = 0; i < length; i++) {
            serialization_detail::TTag<T>::readData(value[i], file);
        }
    }
};

NS_FT_END
