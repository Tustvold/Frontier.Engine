#pragma once

#include "Frontier.h"
#include <FTPtr.h>

#define DEBUG_FT_ALLOC
#ifdef DEBUG_FT_ALLOC
#include <atomic>
#endif


class FTObject {
public:

#ifdef DEBUG_FT_ALLOC
	static std::atomic<unsigned long> ft_object_alive_count_;
	static_assert(ATOMIC_LONG_LOCK_FREE == 2, "FT Alloc Debug requires lock free atomic long");
#endif

	FTObject() : reference_count_(1) {
#ifdef DEBUG_FT_ALLOC
		++ft_object_alive_count_;
#endif
	}

	virtual ~FTObject() {
#ifdef DEBUG_FT_ALLOC
		--ft_object_alive_count_;
#endif
	}

	void release() {
		//FTAssert(reference_count_ != 0, "Reference Count should be greater than 0");
		if (--reference_count_ == 0) {
			delete this;
		}
	}


	void retain() {
		++reference_count_;
	}

	virtual bool isEqual(const FTObject* a) const {
		return a == this;
	}

	virtual size_t hash() const {
		return 0;
	}

private:

	std::atomic<unsigned short> reference_count_;

	static_assert(ATOMIC_SHORT_LOCK_FREE == 2, "FTObject requires lock free atomic short");
};
