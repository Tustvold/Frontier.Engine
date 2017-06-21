#pragma once

#include "Frontier.h"
#include <type_traits>
#include "Util/BTF/Buffer.h"
#include <vector>
#include <unordered_map>


namespace detail {
    template<typename T>
    struct TagID : public std::false_type {};

#define TAGID_ASSIGNMENT(type, _id) \
    template <> struct TagID<type> : public std::true_type { \
        static void readID(std::istream* istream) {\
            const char id = _id;\
            char in_id;\
            istream->read(&in_id, 1);\
            FTAssert(in_id == id, "Invalid ID - expected %i got %i", id, in_id);\
        }\
        static void writeID(std::ostream* ostream) {\
            const char id = _id;\
            ostream->write(&id, 1);\
        }\
    }

#define T_TAGID_ASSIGNMENT(type, _id) \
    template <typename T> struct TagID<type<T>> : public std::true_type { \
        static void readID(std::istream* istream) {\
            const char id = _id;\
            char in_id;\
            istream->read(&in_id, 1);\
            FTAssert(in_id == id, "Invalid ID - expected %i got %i", id, in_id);\
            TagID<T>::readID(istream);\
        }\
        static void writeID(std::ostream* ostream) {\
            const char id = _id;\
            ostream->write(&id, 1);\
            TagID<T>::writeID(ostream);\
        }\
    }

#define T2_TAGID_ASSIGNMENT(type, _id) \
    template <typename T1, typename T2> struct TagID<type<T1,T2>> : public std::true_type { \
        static void readID(std::istream* istream) {\
            const char id = _id;\
            char in_id;\
            istream->read(&in_id, 1);\
            FTAssert(in_id == id, "Invalid ID - expected %i got %i", id, in_id);\
            TagID<T1>::readID(istream);\
            TagID<T2>::readID(istream);\
        }\
        static void writeID(std::ostream* ostream) {\
            const char id = _id;\
            ostream->write(&id, 1);\
            TagID<T1>::writeID(ostream);\
            TagID<T2>::writeID(ostream);\
        }\
    }


    TAGID_ASSIGNMENT(uint8_t, 0);

    TAGID_ASSIGNMENT(uint16_t, 1);

    TAGID_ASSIGNMENT(uint32_t, 2);

    TAGID_ASSIGNMENT(int8_t, 3);

    TAGID_ASSIGNMENT(int16_t, 4);

    TAGID_ASSIGNMENT(int32_t, 5);

    TAGID_ASSIGNMENT(char, 6);

    TAGID_ASSIGNMENT(float, 7);

    TAGID_ASSIGNMENT(double, 8);

    T_TAGID_ASSIGNMENT(std::vector, 100);

    T_TAGID_ASSIGNMENT(std::basic_string, 101);

    T2_TAGID_ASSIGNMENT(std::unordered_map, 102);

    template<typename T>
    struct TagID<std::tuple<T>> : public std::true_type {
        static void readID(std::istream* istream) {
            TagID<T>::readID(istream);
        }

        static void writeID(std::ostream *ostream) {
            TagID<T>::writeID(ostream);
        }

    };

    template<typename T, typename... Others>
    struct TagID<std::tuple<T, Others...>> : public std::true_type {
        static void readID(std::istream* istream) {
            TagID<T>::readID(istream);
            TagID<std::tuple<Others...>>
            ::readID(istream);
        }

        static void writeID(std::ostream *ostream) {
            TagID<T>::writeID(ostream);
            TagID<std::tuple<Others...>>
            ::writeID(ostream);
        }

    };
}