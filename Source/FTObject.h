#pragma once

#include "Frontier.h"
#include <memory>
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

	FTObject() {
#ifdef DEBUG_FT_ALLOC
		++ft_object_alive_count_;
#endif
	}

	virtual ~FTObject() {
#ifdef DEBUG_FT_ALLOC
		--ft_object_alive_count_;
#endif
	}

private:

};
