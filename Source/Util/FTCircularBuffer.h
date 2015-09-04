#pragma once

template <typename T>
class FTCircularBuffer {
public:
    explicit FTCircularBuffer(size_t buffer_size) : buffer_(new T[buffer_size + 1]), buffer_size_(buffer_size), buffer_read_index_(0), buffer_write_index_(0) {
    }


    ~FTCircularBuffer() {
        delete [] buffer_;
    }

    bool isFull() {
        return buffer_write_index_ == buffer_read_index_ - 1;
    }

    bool isEmpty() {
        return buffer_read_index_ == buffer_write_index_;
    }

    bool add(const T& obj) {
        if (isFull())
            return false;

        buffer_[buffer_write_index_++] = obj;
        if (buffer_write_index_ == buffer_size_ + 1)
            buffer_write_index_ = 0;

        return true;
    }

    const T& peekNext() {
        FTAssert(!isEmpty(), "Cannot read from empty circular buffer");
        return buffer_[buffer_read_index_];
    }

    const T& popNext() {
        FTAssert(!isEmpty(), "Cannot read from empty circular buffer");

        const T& ret = buffer_[buffer_read_index_++];
        if (buffer_read_index_ == buffer_size_ + 1)
            buffer_read_index_ = 0;
        return ret;
    }

private:
    T* buffer_;
    size_t buffer_size_;
    size_t buffer_read_index_;
    size_t buffer_write_index_;
};
