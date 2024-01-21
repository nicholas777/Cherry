#pragma once

#ifdef CH_PLATFORM_WINDOWS

#endif

#ifdef CH_DEBUG_MODE
	#define CH_ENABLE_ASSERTS 1
#endif

#ifdef CH_RELEASE_MODE
    #define CH_ENABLE_ASSERTS 1
#endif

#ifdef CH_DIST_MODE
    #define CH_ENABLE_ASSERTS 0
#endif

#if CH_ENABLE_ASSERTS == 1
    #include <assert.h>
	#define CH_ASSERT(condition, error) { assert(condition); }
#else
	#define CH_ASSERT(condition, error)
#endif
