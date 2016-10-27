#pragma once

#include "Buffer.h"

struct CompressionBuffer : public Buffer {

	static std::unique_ptr<CompressionBuffer> readFile(FILE *fp) {
		auto temp = std::make_unique<CompressionBuffer>();

		size_t bytesRead = 0;

		do {
			if (temp->buffer_reserve(temp->len + CHUNK_SIZE))
			FTAssert(false, "Buffer out of memory");
			bytesRead = fread(temp->data + temp->len, 1, CHUNK_SIZE, fp);
			temp->len += bytesRead;
		} while (!feof(fp));

		return temp->decompressBuffer();
	}

	int writeFile(FILE *fp) {
        auto ret = compressBuffer();
        ret->Buffer::writeFile(fp);
	}

private:
    std::unique_ptr<CompressionBuffer> compressBuffer();
    std::unique_ptr<CompressionBuffer> decompressBuffer();
};