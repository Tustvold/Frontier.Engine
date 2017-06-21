#pragma once

#include "TagID.h"
#include <ttvfs.h>

namespace detail {
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

        static T readData(ttvfs::File *file) {
            T value;
            fileRead(file, &value);
            return value;
        }

        static void writeData(const T &value, ttvfs::File *file) {
            fileWrite(file, &value);
        }
    };

    template<typename T>
    class TTag<std::vector<T>> {
    public:

        static std::vector<T> readData(ttvfs::File *file) {
            std::vector<T> value;
            uint32_t size;

            fileRead(file, &size);
            value.reserve(size);
            for (uint32_t i = 0; i < size; i++) {
                value.emplace_back(TTag<T>::readData(file));
            }
            return value;
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

        static std::string readData(ttvfs::File *file) {
            uint32_t size;
            fileRead(file, &size);
            std::string out;
            out.resize(size);

            file->read(&out[0], size);
            return out;
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

        static std::unordered_map<T1,T2> readData(ttvfs::File *file) {
            uint32_t size;
            fileRead(file, &size);
            std::unordered_map<T1,T2> ret;
            ret.reserve(size);
            for (uint32_t i = 0; i < size; i++) {
                auto pair = TTag<std::tuple<T1, T2>>::readData(file);
                ret[std::get<0>(pair)] = std::get<1>(pair);
            }
            return ret;
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
        static std::tuple<T> readData(ttvfs::File *file) {
            std::tuple<T> ret = std::make_tuple(TTag<T>::readData(file));
            return ret;
        }

        static void writeData(const Tuple &value, ttvfs::File *file) {
            TTag<T>::writeData(std::get<0>(value), file);
        }
    };

    template<typename T, typename... Others>
    class TTag<std::tuple<T, Others...>> {
        using Tuple = std::tuple<T, Others...>;

    public:

        static std::tuple<T, Others...> readData(ttvfs::File *file) {
            std::tuple<T> ret = std::make_tuple(TTag<T>::readData(file));
            std::tuple<Others...> others = TTag<std::tuple<Others...>>::readData(file);
            return std::tuple_cat(ret, others);
        }

        static void writeData(const Tuple &value, ttvfs::File *file) {
            TupleWriter<Tuple, std::tuple_size<Tuple>::value>::write(value, file);
        }

    };
}