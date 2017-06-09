
#include "CompressionBuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <algorithm>

static std::unique_ptr<CompressionBuffer> compress(const void *mem, size_t len) {

	auto ret = std::make_unique<CompressionBuffer>();
	z_stream stream;

	stream.zalloc = Z_NULL;
	stream.zfree = Z_NULL;
	stream.opaque = Z_NULL;
	stream.next_in = (unsigned char *) mem;
	stream.avail_in = len;

	int windowbits = 15;

	if (deflateInit2(&stream,
	Z_DEFAULT_COMPRESSION,
	Z_DEFLATED,
	windowbits,
	8,
	Z_DEFAULT_STRATEGY
	) != Z_OK) {
		FTAssert(false, "Compression error");
	}

	do {
		if (ret->buffer_reserve(ret->len + CHUNK_SIZE))
		FTAssert(false, "Compression error");

		stream.next_out = ret->data + ret->len;
		stream.avail_out = CHUNK_SIZE;

		if (deflate(&stream, Z_FINISH) == Z_STREAM_ERROR)
		FTAssert(false, "Compression error");

		ret->len += CHUNK_SIZE - stream.avail_out;
	} while (stream.avail_out == 0);
	(void) deflateEnd(&stream);

	return ret;
}

static std::unique_ptr<CompressionBuffer> decompress(const void *mem, size_t len) {
     	auto ret = std::make_unique<CompressionBuffer>();

	z_stream stream;

	stream.zalloc = Z_NULL;
	stream.zfree = Z_NULL;
	stream.opaque = Z_NULL;
	stream.next_in = (unsigned char *) mem;
	stream.avail_in = len;

	/* "Add 32 to windowBits to enable zlib and gzip decoding with automatic
	 * header detection" */
	if (inflateInit2(&stream, 15 + 32) != Z_OK)
	FTAssert(false, "Decompression error");

	int zlib_ret;

	do {
		if (ret->buffer_reserve(ret->len + CHUNK_SIZE))
		FTAssert(false, "Decompression error");

		stream.avail_out = CHUNK_SIZE;
		stream.next_out = ret->data + ret->len;

		switch ((zlib_ret = inflate(&stream, Z_NO_FLUSH))) {
			case Z_MEM_ERROR:
				FTAssert(false, "Decompression error - out of memory");

			case Z_DATA_ERROR:
			case Z_NEED_DICT:
				FTAssert(false, "Decompression error");

			default:
				/* update our buffer length to reflect the new data */
				ret->len += CHUNK_SIZE - stream.avail_out;
		}
	} while (stream.avail_out == 0);

	if (zlib_ret != Z_STREAM_END)
	FTAssert(false, "Decompression error");
	(void) inflateEnd(&stream);

	return ret;
}

std::unique_ptr<CompressionBuffer> CompressionBuffer::compressBuffer() {
    return compress(data, len);
}

std::unique_ptr<CompressionBuffer> CompressionBuffer::decompressBuffer() {
	return decompress(data, len);
}



