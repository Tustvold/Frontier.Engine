#pragma once

#include "Frontier.h"
#include <type_traits>
#include "Buffer.h"
#include <vector>

class TagBase {
public:
    template<typename T>
    static void write(const T& value, Buffer* buffer);

    template<typename T>
    static T read(Buffer* buffer);
};

namespace detail {
    template<typename T>
    class TTag : public TagBase {
        static_assert(std::is_arithmetic<T>::value, "Only Arithmetic types supported");

    public:

        static T read(Buffer *buffer, bool embedded = false) {
            T value;
            if (!embedded) {
                verifyID(buffer);
            }
            buffer->read(&value);
            return value;
        }

        static void write(const T &value, Buffer *buffer) {
            writeID(buffer);
            writeData(value, buffer);
        }

        static constexpr uint8_t getID() {
            return (std::is_signed<T>::value ? 1 << 4 : 0) | sizeof(T);
        }

        static void verifyID(Buffer *buffer) {
            uint8_t in_id;
            buffer->read(&in_id);
            FTAssert(in_id == getID(), "Invalid ID - expected %i got %i", getID(), in_id);
        }

        static void writeID(Buffer *buffer) {
            const uint8_t id = getID();
            buffer->write(&id);
        }

        static void writeData(const T &value, Buffer *buffer) {
            buffer->write(&value);
        }
    };

    template<typename T>
    class TTag<std::vector<T>> : public TagBase {
    public:

        TTag(Buffer *buffer, bool embedded = false) {

        }

        static std::vector<T> read(Buffer *buffer, bool embedded = false) {
            std::vector<T> value;
            size_t size;

            if (!embedded) {
                verifyID(buffer);
            }

            buffer->read(&size);
            value.reserve(size);
            for (size_t i = 0; i < size; i++) {
                value.emplace_back(TTag<T>::read(buffer, true));
            }
            return value;
        }

        static void write(const std::vector<T> &value, Buffer *buffer) {
            writeID(buffer);
            writeData(value, buffer);
        }

        static constexpr uint8_t getID() {
            return 2 << 5 | 1;
        }

        static void verifyID(Buffer *buffer) {
            uint8_t in_id;
            buffer->read(&in_id);
            FTAssert(in_id == getID(), "Invalid ID - expected %i got %i", getID(), in_id);
            TTag<T>::verifyID(buffer);
        }

        static void writeID(Buffer *buffer) {
            const uint8_t id = getID();
            buffer->write(&id);
            TTag<T>::writeID(buffer);
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
    class TTag<std::basic_string<T>> : public TagBase {
    public:

        static std::basic_string<T> read(Buffer *buffer, bool embedded = false) {
            if (!embedded) {
                verifyID(buffer);
            }

            size_t size;
            buffer->read(&size);
            T *start = (T *) buffer->readBytes(sizeof(T) * size);
            return std::basic_string<T>(start, start + size);
        }

        static void write(const std::basic_string<T> &value, Buffer *buffer) {
            writeID(buffer);
            writeData(value, buffer);
        }

        static constexpr uint8_t getID() {
            return 3 << 5 | (std::is_signed<T>::value ? 1 << 4 : 0) | sizeof(T);
        }

        static void verifyID(Buffer *buffer) {
            uint8_t in_id;
            buffer->read(&in_id);
            FTAssert(in_id == getID(), "Invalid ID - expected %i got %i", getID(), in_id);
        }

        static void writeID(Buffer *buffer) {
            const uint8_t id = getID();
            buffer->write(&id);
        }

        static void writeData(const std::basic_string<T> &value, Buffer *buffer) {
            size_t size = value.size();
            buffer->write(&size);
            buffer->write(value.data(), size);
        }
    };
}

template<typename T>
void TagBase::write(const T& value, Buffer *buffer) {
    detail::TTag<T>::write(value, buffer);
}

template<typename T>
T TagBase::read(Buffer *buffer) {
    return detail::TTag<T>::read(buffer);
}
