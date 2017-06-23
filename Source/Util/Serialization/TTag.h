#pragma once

#include "TagID.h"
#include <ttvfs.h>

namespace serialization_detail {
    template <typename T>
    void fileRead(ttvfs::File *file, T *output, uint32_t n = 1) {
        file->read(reinterpret_cast<char*>(output), sizeof(T) * n);
    }

    template <typename T>
    void fileWrite(ttvfs::File *file, T *output, uint32_t n = 1) {
        file->write(reinterpret_cast<const char*>(output), sizeof(T) * n);
    }

    template<typename T>
    class TTag {
        static_assert(std::is_arithmetic<T>::value, "Only Arithmetic types supported");

    public:

        static void readData(T& value, ttvfs::File *file) {
            fileRead(file, &value);
        }

        static void writeData(const T &value, ttvfs::File *file) {
            fileWrite(file, &value);
        }
    };

    template <typename T, uint32_t N>
    class TTag<T[N]> {
    public:

        static void readData(T ret[N], ttvfs::File *file) {
            for (uint32_t i = 0; i < N; i++) {
                TTag<T>::readData(ret[i], file);
            }
        }

        static void writeData(const T value[N], ttvfs::File *file) {
            for (uint32_t i = 0; i < N; i++) {
                TTag<T>::writeData(value[i], file);
            }
        }
    };

    template<typename T>
    class TTag<std::vector<T>> {
    public:

        static void readData(std::vector<T>& ret, ttvfs::File *file) {
            uint32_t size;

            fileRead(file, &size);
            ret.resize(size);
            for (uint32_t i = 0; i < size; i++) {
                TTag<T>::readData(ret[i], file);
            }
        }

        static void writeData(const std::vector<T> &value, ttvfs::File *file) {
            uint32_t size = (uint32_t) value.size();
            fileWrite(file, &size);
            for (uint32_t i = 0; i < size; i++) {
                TTag<T>::writeData(value[i], file);
            }
        }
    };

    template <>
    class TTag<std::string> {
    public:

        static void readData(std::string& ret, ttvfs::File *file) {
            uint32_t size;
            fileRead(file, &size);
            ret.resize(size);

            file->read(&ret[0], size);
        }

        static void writeData(const std::string &value, ttvfs::File *file) {
            uint32_t size = (uint32_t) value.size();
            fileWrite(file, &size);
            fileWrite(file, value.data(), size);
        }
    };

    template<typename T1, typename T2>
    class TTag<std::unordered_map<T1,T2>> {

    public:

        static void readData(std::unordered_map<T1,T2>& ret, ttvfs::File *file) {
            uint32_t size;
            fileRead(file, &size);
            ret.reserve(size);
            for (uint32_t i = 0; i < size; i++) {
                std::tuple<T1, T2> pair;
                TTag<std::tuple<T1, T2>>::readData(pair, file);
                ret[std::get<0>(pair)] = std::get<1>(pair);
            }
        }

        static void writeData(const std::unordered_map<T1,T2>&value, ttvfs::File *file) {
            uint32_t size = (uint32_t) value.size();
            fileWrite(file, &size);
            for (auto it = value.begin(); it != value.end(); ++it) {
                TTag<std::tuple<T1, T2>>::writeData(std::make_tuple(it->first, it->second), file);
            }
        }
    };

    template<typename Tuple, uint32_t _I>
    class TupleWriter {
        static constexpr uint32_t I = (const uint32_t) (std::tuple_size<Tuple>::value - _I);

    public:
        static void write(const Tuple &value, ttvfs::File *file) {
            TTag<typename std::tuple_element<I, Tuple>::type>::writeData(std::get<I>(value), file);
            TupleWriter<Tuple, _I - 1>::write(value, file);
        }
    };

    template<typename Tuple>
    class TupleWriter<Tuple, 1> {
        static constexpr uint32_t I = (const uint32_t) (std::tuple_size<Tuple>::value - 1);

    public:
        static void write(const Tuple &value, ttvfs::File *file) {
            TTag<typename std::tuple_element<I, Tuple>::type>::writeData(std::get<I>(value), file);
        }
    };

    template<typename T>
    class TTag<std::tuple<T>> {
        using Tuple = std::tuple<T>;

    public:
        static void readData(std::tuple<T>& ret, ttvfs::File *file) {
            T val;
            TTag<T>::readData(val, file);
            ret = std::make_tuple(val);
        }

        static void writeData(const Tuple &value, ttvfs::File *file) {
            TTag<T>::writeData(std::get<0>(value), file);
        }
    };

    template<typename T, typename... Others>
    class TTag<std::tuple<T, Others...>> {
        using Tuple = std::tuple<T, Others...>;

    public:

        static void readData(std::tuple<T, Others...>& ret, ttvfs::File *file) {
            T ret2;
            TTag<T>::readData(ret2, file);
            std::tuple<Others...> others;
            TTag<std::tuple<Others...>>::readData(others, file);
            ret = std::tuple_cat(std::make_tuple(ret2), others);
        }

        static void writeData(const Tuple &value, ttvfs::File *file) {
            TupleWriter<Tuple, std::tuple_size<Tuple>::value>::write(value, file);
        }

    };
}