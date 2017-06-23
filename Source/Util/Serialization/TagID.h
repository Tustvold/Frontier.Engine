#pragma once

#include "Frontier.h"
#include <ttvfs.h>
#include <type_traits>
#include <vector>
#include <unordered_map>


namespace serialization_detail {
    template<typename T>
    struct TagID : public std::false_type {};

#define TAGID_ASSIGNMENT(type, _id) \
    template <> struct TagID<type> : public std::true_type { \
        static void readID(ttvfs::File* file) {\
            const char id = _id;\
            char in_id;\
            file->read(&in_id, 1);\
            FTAssert(in_id == id, "Invalid ID - expected %i got %i", id, in_id);\
        }\
        static void writeID(ttvfs::File* file) {\
            const char id = _id;\
            file->write(&id, 1);\
        }\
    }

#define T_TAGID_ASSIGNMENT(type, _id) \
    template <typename T> struct TagID<type<T>> : public std::true_type { \
        static void readID(ttvfs::File* file) {\
            const char id = _id;\
            char in_id;\
            file->read(&in_id, 1);\
            FTAssert(in_id == id, "Invalid ID - expected %i got %i", id, in_id);\
            TagID<T>::readID(file);\
        }\
        static void writeID(ttvfs::File* file) {\
            const char id = _id;\
            file->write(&id, 1);\
            TagID<T>::writeID(file);\
        }\
    }

#define T2_TAGID_ASSIGNMENT(type, _id) \
    template <typename T1, typename T2> struct TagID<type<T1,T2>> : public std::true_type { \
        static void readID(ttvfs::File* file) {\
            const char id = _id;\
            char in_id;\
            file->read(&in_id, 1);\
            FTAssert(in_id == id, "Invalid ID - expected %i got %i", id, in_id);\
            TagID<T1>::readID(file);\
            TagID<T2>::readID(file);\
        }\
        static void writeID(ttvfs::File* file) {\
            const char id = _id;\
            file->write(&id, 1);\
            TagID<T1>::writeID(file);\
            TagID<T2>::writeID(file);\
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
    static_assert(sizeof(float) == 4, "Invalid float size");

    TAGID_ASSIGNMENT(double, 8);
    static_assert(sizeof(double) == 8, "Invalid double size");

    TAGID_ASSIGNMENT(size_t, 9);
    static_assert(sizeof(size_t) == 8, "Invalid size_t");


    T_TAGID_ASSIGNMENT(std::vector, 100);

    T_TAGID_ASSIGNMENT(std::basic_string, 101);

    T2_TAGID_ASSIGNMENT(std::unordered_map, 102);

    template <typename T, uint32_t N>
    struct TagID<T[N]> : public std::true_type {
        static void readID(ttvfs::File* file) {
            const char id = 103;
            char in_id;
            file->read(&in_id, 1);
            FTAssert(in_id == id, "Invalid ID - expected %i got %i", id, in_id);
            uint32_t size;
            file->read(&size, sizeof(uint32_t));
            FTAssert(size == N, "Invalid Size - expected %i got %i", N, size);
            TagID<T>::readID(file);
        }
        static void writeID(ttvfs::File* file) {
            const char id = 103;
            file->write(&id, 1);
            uint32_t size = N;
            file->write(&size, sizeof(uint32_t));
            TagID<T>::writeID(file);
        }
    };

    template <typename T>
    struct TagID<T[]> : public std::true_type {
        static void readID(ttvfs::File* file) {
            const char id = 104;
            char in_id;
            file->read(&in_id, 1);
            FTAssert(in_id == id, "Invalid ID - expected %i got %i", id, in_id);
            TagID<T>::readID(file);
        }
        static void writeID(ttvfs::File* file) {
            const char id = 104;
            file->write(&id, 1);
            TagID<T>::writeID(file);
        }
    };

    template<typename T>
    struct TagID<std::tuple<T>> : public std::true_type {
        static void readID(ttvfs::File* file) {
            TagID<T>::readID(file);
        }

        static void writeID(ttvfs::File *file) {
            TagID<T>::writeID(file);
        }

    };

    template<typename T, typename... Others>
    struct TagID<std::tuple<T, Others...>> : public std::true_type {
        static void readID(ttvfs::File* file) {
            TagID<T>::readID(file);
            TagID<std::tuple<Others...>>
            ::readID(file);
        }

        static void writeID(ttvfs::File *file) {
            TagID<T>::writeID(file);
            TagID<std::tuple<Others...>>
            ::writeID(file);
        }

    };
}