#ifndef __Buffer_H__
#define __Buffer_H__

#include <stddef.h>
#include <stdio.h>
#include <VFSFile.h>
#include "Frontier.h"
#include <cstring>

//The number of bytes to process at once
#define CHUNK_SIZE 4096
#define LAZY_INIT_CAP 512

class Buffer {
public:
	unsigned char *data;

	size_t len;
	size_t cap;

	size_t cpos;

	Buffer();

	virtual ~Buffer();

    /*
     * Copies `n' bytes from `data' into the buffer. Returns non-zero if an
     * out-of-memory failure occured. If such a failure occurs, further usage of the
     * buffer results in undefined behavior.
     */
	int buffer_append(const void *data, size_t n);

	static Buffer *readFile(ttvfs::File* fp) {
		Buffer *ret = new Buffer();

		size_t bytesRead = 0;

		do {
			if (ret->buffer_reserve(ret->len + CHUNK_SIZE))
			FTAssert(false, "Buffer out of memory");
			bytesRead = fp->read(ret->data + ret->len, CHUNK_SIZE);
			ret->len += bytesRead;
		} while (!fp->iseof());

		return ret;
	}

	virtual int writeFile(ttvfs::File* fp) {
		const char *cdata = (const char *) data;
		size_t bytes_left = len;

		size_t bytes_written = 0;

		do {
			bytes_written = fp->write(cdata, bytes_left);

			bytes_left -= bytes_written;
			cdata += bytes_written;
		} while (bytes_left > 0);

		return 0;
	}

	unsigned char *readBytes(size_t number) {
		unsigned char *ptr = data + cpos;
		cpos += number;
		return ptr;
	}

	void resetIndex() {
		cpos = 0;
	}

	template <typename T>
	void read(T* output, size_t n = 1) {
		memcpy(output, readBytes(sizeof(T) * n), sizeof(T) * n);
	}

    template <typename T>
    void write(T* input, size_t n = 1) {
        buffer_append(input, sizeof(T) * n);
    }

    size_t length() {
        return len;
    }

	void seek(size_t pos) {
		cpos = pos;
	}

    size_t getPos() {
        return cpos;
    }

    /*
* Ensures there's enough room in the buffer for at least `reserved_amount'
* bytes. Returns non-zero on failure. If such a failure occurs, the buffer
* is deallocated and set to one which can be passed to buffer_free. Any other
* usage is undefined.
*/
    int buffer_reserve(size_t reserved_amount);

private:
	int lazy_init();
};

#endif
