#pragma once

#include <VFSFile.h>
#include "Buffer.h"

struct CompressionBuffer : public Buffer {

	static std::unique_ptr<CompressionBuffer> readFile(ttvfs::File *fp) {
		std::unique_ptr<CompressionBuffer> temp = std::make_unique<CompressionBuffer>();

		size_t bytesRead = 0;

		auto t = fp->size();
        (void)t;

		do {
			FTAssert(temp->buffer_reserve(temp->len + CHUNK_SIZE) == 0, "Buffer out of memory");
			bytesRead = fp->read(temp->data + temp->len, CHUNK_SIZE);
			temp->len += bytesRead;
		} while (!fp->iseof());

		return temp->decompressBuffer();
	}



	int writeFile(ttvfs::File *fp) {
        auto ret = compressBuffer();
        return ret->Buffer::writeFile(fp);
	}

private:
    std::unique_ptr<CompressionBuffer> compressBuffer();
    std::unique_ptr<CompressionBuffer> decompressBuffer();
};