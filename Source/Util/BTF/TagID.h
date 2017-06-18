#pragma once

#include "Frontier.h"
#include <type_traits>
#include "Buffer.h"
#include <vector>
#include <unordered_map>


namespace Serialization {
    template<typename T>
    struct TagID;

#define TAGID_ASSIGNMENT(type, _id) \
    template <> struct TagID<type> { \
        static void readID(Buffer* buffer) {\
            const uint8_t id = _id;\
            uint8_t in_id;\
            buffer->read(&in_id);\
            FTAssert(in_id == id, "Invalid ID - expected %i got %i", id, in_id);\
        }\
        static void writeID(Buffer* buffer) {\
            const uint8_t id = _id;\
            buffer->write(&id);\
        }\
    }

#define T_TAGID_ASSIGNMENT(type, _id) \
    template <typename T> struct TagID<type<T>> { \
        static void readID(Buffer* buffer) {\
            const uint8_t id = _id;\
            uint8_t in_id;\
            buffer->read(&in_id);\
            FTAssert(in_id == id, "Invalid ID - expected %i got %i", id, in_id);\
            TagID<T>::readID(buffer);\
        }\
        static void writeID(Buffer* buffer) {\
            const uint8_t id = _id;\
            buffer->write(&id);\
            TagID<T>::writeID(buffer);\
        }\
    }

#define T2_TAGID_ASSIGNMENT(type, _id) \
    template <typename T1, typename T2> struct TagID<type<T1,T2>> { \
        static void readID(Buffer* buffer) {\
            const uint8_t id = _id;\
            uint8_t in_id;\
            buffer->read(&in_id);\
            FTAssert(in_id == id, "Invalid ID - expected %i got %i", id, in_id);\
            TagID<T1>::readID(buffer);\
            TagID<T2>::readID(buffer);\
        }\
        static void writeID(Buffer* buffer) {\
            const uint8_t id = _id;\
            buffer->write(&id);\
            TagID<T1>::writeID(buffer);\
            TagID<T2>::writeID(buffer);\
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
    struct TagID<std::tuple<T>> {
        static void readID(Buffer *buffer) {
            TagID<T>::readID(buffer);
        }

        static void writeID(Buffer *buffer) {
            TagID<T>::writeID(buffer);
        }

    };

    template<typename T, typename... Others>
    struct TagID<std::tuple<T, Others...>> {
        static void readID(Buffer *buffer) {
            TagID<T>::readID(buffer);
            TagID<std::tuple<Others...>>
            ::readID(buffer);
        }

        static void writeID(Buffer *buffer) {
            TagID<T>::writeID(buffer);
            TagID<std::tuple<Others...>>
            ::writeID(buffer);
        }

    };
}