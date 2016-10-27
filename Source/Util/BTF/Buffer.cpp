
#include "Buffer.h"
#include "Frontier.h"

#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <malloc.h>


int Buffer::lazy_init() {
	cap = LAZY_INIT_CAP;
	data = (unsigned char*) malloc(cap);
	len = 0;

	if (data == NULL)
		return 1;
	return 0;
}

Buffer::Buffer() {
	data = NULL;
	len = 0;
	cap = 0;
	cpos = 0;
}

Buffer::~Buffer() {
	free(this->data);

	data = NULL;
	len = 0;
	cap = 0;
	cpos = 0;
}

int Buffer::buffer_reserve(size_t reserved_amount) {
	if (data == NULL &&
			lazy_init())
		return 1;

	if (cap >= reserved_amount)
		return 0;

	while (cap < reserved_amount)
		cap *= 2;

	unsigned char *temp = (unsigned char *) realloc(data, cap);

	if (temp == NULL)
		return this->~Buffer(), 1;

	data = temp;

	return 0;
}

int Buffer::buffer_append(const void *data, size_t n) {
	if (this->data == NULL &&
			lazy_init())
		return 1;

	if (buffer_reserve(this->len + n))
		return 1;

	memcpy(this->data + this->len, data, n);
	this->len += n;

	return 0;
}