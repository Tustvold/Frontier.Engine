#pragma once

#include "TagID.h"
#include <iostream>

namespace detail {
    template <typename T>
    void istreamRead(std::istream *str, T* output, uint32_t n = 1) {
        str->read(reinterpret_cast<char*>(output), sizeof(T) * n);
    }

    template <typename T>
    void ostreamWrite(std::ostream *str, T* output, uint32_t n = 1) {
        str->write(reinterpret_cast<const char*>(output), sizeof(T) * n);
    }

    template<typename T>
    class TTag {
        static_assert(std::is_arithmetic<T>::value, "Only Arithmetic types supported");

    public:

        static T readData(std::istream *str) {
            T value;
            istreamRead(str, &value);
            return value;
        }

        static void writeData(const T &value, std::ostream *str) {
            ostreamWrite(str, &value);
        }
    };

    template<typename T>
    class TTag<std::vector<T>> {
    public:

        static std::vector<T> readData(std::istream *str) {
            std::vector<T> value;
            uint32_t size;

            istreamRead(str, &size);
            value.reserve(size);
            for (uint32_t i = 0; i < size; i++) {
                value.emplace_back(TTag<T>::readData(str));
            }
            return value;
        }

        static void writeData(const std::vector<T> &value, std::ostream *str) {
            uint32_t size = (uint32_t) value.size();
            ostreamWrite(str, &size);
            for (uint32_t i = 0; i < size; i++) {
                TTag<T>::writeData(value[i], str);
            }
        }
    };

    template <>
    class TTag<std::string> {
    public:

        static std::string readData(std::istream *str) {
            uint32_t size;
            istreamRead(str, &size);
            std::string out;
            out.reserve(size);
            auto it = std::istreambuf_iterator<char>(*str);
            std::copy_n(it, size, std::back_inserter(out));
            ++it;
            return out;
        }

        static void writeData(const std::string &value, std::ostream *str) {
            uint32_t size = (uint32_t) value.size();
            ostreamWrite(str, &size);
            ostreamWrite(str, value.data(), size);
        }
    };

    template<typename T1, typename T2>
    class TTag<std::unordered_map<T1,T2>> {

    public:

        static std::unordered_map<T1,T2> readData(std::istream *str) {
            uint32_t size;
            istreamRead(str, &size);
            std::unordered_map<T1,T2> ret;
            ret.reserve(size);
            for (uint32_t i = 0; i < size; i++) {
                auto pair = TTag<std::tuple<T1, T2>>::readData(str);
                ret[std::get<0>(pair)] = std::get<1>(pair);
            }
            return ret;
        }

        static void writeData(const std::unordered_map<T1,T2>&value, std::ostream *str) {
            uint32_t size = (uint32_t) value.size();
            ostreamWrite(str, &size);
            for (auto it = value.begin(); it != value.end(); ++it) {
                TTag<std::tuple<T1, T2>>::writeData(std::make_tuple(it->first, it->second), str);
            }
        }
    };

    template<typename Tuple, uint32_t _I>
    class TupleWriter {
        static constexpr uint32_t I = (const uint32_t) (std::tuple_size<Tuple>::value - _I);

    public:
        static void write(const Tuple &value, std::ostream *str) {
            TTag<typename std::tuple_element<I, Tuple>::type>::writeData(std::get<I>(value), str);
            TupleWriter<Tuple, _I - 1>::write(value, str);
        }
    };

    template<typename Tuple>
    class TupleWriter<Tuple, 1> {
        static constexpr uint32_t I = (const uint32_t) (std::tuple_size<Tuple>::value - 1);

    public:
        static void write(const Tuple &value, std::ostream *str) {
            TTag<typename std::tuple_element<I, Tuple>::type>::writeData(std::get<I>(value), str);
        }
    };

    template<typename T>
    class TTag<std::tuple<T>> {
        using Tuple = std::tuple<T>;

    public:
        static std::tuple<T> readData(std::istream *str) {
            std::tuple<T> ret = std::make_tuple(TTag<T>::readData(str));
            return ret;
        }

        static void writeData(const Tuple &value, std::ostream *str) {
            TTag<T>::writeData(std::get<0>(value), str);
        }
    };

    template<typename T, typename... Others>
    class TTag<std::tuple<T, Others...>> {
        using Tuple = std::tuple<T, Others...>;

    public:

        static std::tuple<T, Others...> readData(std::istream *str) {
            std::tuple<T> ret = std::make_tuple(TTag<T>::readData(str));
            std::tuple<Others...> others = TTag<std::tuple<Others...>>::readData(str);
            return std::tuple_cat(ret, others);
        }

        static void writeData(const Tuple &value, std::ostream *str) {
            TupleWriter<Tuple, std::tuple_size<Tuple>::value>::write(value, str);
        }

    };
}