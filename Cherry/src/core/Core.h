#pragma once

// TODO: Clean up dependencies and add copyright stuff

#ifdef CH_PLATFORM_WINDOWS

#endif

#ifdef CH_DEBUG_MODE
	#define CH_TRACE(...) Cherry::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define CH_INFO(...) Cherry::Log::GetClientLogger()->info(__VA_ARGS__)
	#define CH_WARNING(...) Cherry::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define CH_ERROR(...) Cherry::Log::GetClientLogger()->error(__VA_ARGS__)
	#define CH_FATAL(...) Cherry::Log::GetClientLogger()->fatal(__VA_ARGS__)
	                   
	#define CH_ENABLE_ASSERTS 1
#endif

#ifdef CH_RELEASE_MODE
	#define CH_TRACE(...) Cherry::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define CH_INFO(...) Cherry::Log::GetClientLogger()->info(__VA_ARGS__)
	#define CH_WARNING(...) Cherry::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define CH_ERROR(...) Cherry::Log::GetClientLogger()->error(__VA_ARGS__)
	#define CH_FATAL(...) Cherry::Log::GetClientLogger()->fatal(__VA_ARGS__)

	#define CH_ENABLE_ASSERTS 0
#endif

#ifdef CH_DIST_MODE
	#define CH_TRACE(...)
	#define CH_INFO(...)
	#define CH_WARNING(...)
	#define CH_ERROR(...)
	#define CH_FATAL(...)

	#define CH_ENABLE_ASSERTS 0
#endif

#if CH_ENABLE_ASSERTS == 1
	#define CH_ASSERT(condition, error) { if(!(condition)) { CH_ERROR(error); __debugbreak(); } }
	#define CH_VALIDATE(condition) { if(!(condition)) { __debugbreak(); } }
#else
	#define CH_ASSERT(condition, error)
#endif