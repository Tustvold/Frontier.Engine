#pragma once

#include "TagID.h"

namespace Serialization {
    template<typename T>
    class TTag {
        static_assert(std::is_arithmetic<T>::value, "Only Arithmetic types supported");

    public:

        static T readData(Buffer *buffer) {
            T value;
            buffer->read(&value);
            return value;
        }

        static void writeData(const T &value, Buffer *buffer) {
            buffer->write(&value);
        }
    };

    template<typename T>
    class TTag<std::vector<T>> {
    public:

        static std::vector<T> readData(Buffer *buffer) {
            std::vector<T> value;
            size_t size;

            buffer->read(&size);
            value.reserve(size);
            for (size_t i = 0; i < size; i++) {
                value.emplace_back(TTag<T>::readData(buffer));
            }
            return value;
        }

        static void writeData(const std::vector<T> &value, Buffer *buffer) {
            size_t size = value.size();
            buffer->write(&size);
            for (size_t i = 0; i < size; i++) {
                TTag<T>::writeData(value[i], buffer);
            }
        }
    };


    template<typename T>
    class TTag<std::basic_string<T>> {

    public:

        static std::basic_string<T> readData(Buffer *buffer) {
            size_t size;
            buffer->read(&size);
            T *start = (T *) buffer->readBytes(sizeof(T) * size);
            return std::basic_string<T>(start, start + size);
        }

        static void writeData(const std::basic_string<T> &value, Buffer *buffer) {
            size_t size = value.size();
            buffer->write(&size);
            buffer->write(value.data(), size);
        }
    };

    template<typename T1, typename T2>
    class TTag<std::unordered_map<T1,T2>> {

    public:

        static std::unordered_map<T1,T2> readData(Buffer *buffer) {
            size_t size;
            buffer->read(&size);
            std::unordered_map<T1,T2> ret;
            ret.reserve(size);
            for (size_t i = 0; i < size; i++) {
                auto pair = TTag<std::tuple<T1, T2>>::readData(buffer);
                ret[std::get<0>(pair)] = std::get<1>(pair);
            }
            return ret;
        }

        static void writeData(const std::unordered_map<T1,T2>&value, Buffer *buffer) {
            size_t size = value.size();
            buffer->write(&size);
            for (auto it = value.begin(); it != value.end(); ++it) {
                TTag<std::tuple<T1, T2>>::writeData(std::make_tuple(it->first, it->second), buffer);
            }
        }
    };

    template<typename Tuple, size_t _I>
    class TupleWriter {
        static constexpr size_t I = std::tuple_size<Tuple>::value - _I;

    public:
        static void write(const Tuple &value, Buffer *buffer) {
            TTag<typename std::tuple_element<I, Tuple>::type>::writeData(std::get<I>(value), buffer);
            TupleWriter<Tuple, _I - 1>::write(value, buffer);
        }
    };

    template<typename Tuple>
    class TupleWriter<Tuple, 1> {
        static constexpr size_t I = std::tuple_size<Tuple>::value - 1;

    public:
        static void write(const Tuple &value, Buffer *buffer) {
            TTag<typename std::tuple_element<I, Tuple>::type>::writeData(std::get<I>(value), buffer);
        }
    };

    template<typename T>
    class TTag<std::tuple<T>> {
        using Tuple = std::tuple<T>;

    public:
        static std::tuple<T> readData(Buffer *buffer) {
            std::tuple<T> ret = std::make_tuple(TTag<T>::readData(buffer));
            return ret;
        }

        static void writeData(const Tuple &value, Buffer *buffer) {
            TTag<T>::writeData(std::get<0>(value), buffer);
        }
    };

    template<typename T, typename... Others>
    class TTag<std::tuple<T, Others...>> {
        using Tuple = std::tuple<T, Others...>;

    public:

        static std::tuple<T, Others...> readData(Buffer *buffer) {
            std::tuple<T> ret = std::make_tuple(TTag<T>::readData(buffer));
            std::tuple<Others...> others = TTag<std::tuple<Others...>>::readData(buffer);
            return std::tuple_cat(ret, others);
        }

        static void writeData(const Tuple &value, Buffer *buffer) {
            TupleWriter<Tuple, std::tuple_size<Tuple>::value>::write(value, buffer);
        }

    };
}