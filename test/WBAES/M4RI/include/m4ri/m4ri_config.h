#ifndef M4RI_M4RI_CONFIG_H
#define M4RI_M4RI_CONFIG_H


#ifdef __ANDROID__
	#define ANDROID_M4RI
#elif defined(__iOS__)
	#define iOS_M4RI
#elif defined(__macOS__)
	#define macOS_M4RI
#elif defined(_WIN32)
	#define win32_M4RI
#endif

#ifdef ANDROID_M4RI
	// Defines determined during configuration of m4ri.
	#define __M4RI_HAVE_MM_MALLOC		1
	#define __M4RI_HAVE_POSIX_MEMALIGN	0
	#define __M4RI_HAVE_SSE2		0
	#define __M4RI_HAVE_OPENMP		0
	#define __M4RI_CPU_L1_CACHE		32768
	#define __M4RI_CPU_L2_CACHE		262144
	#define __M4RI_CPU_L3_CACHE		262144
	#define __M4RI_DEBUG_DUMP		(0 || 0)
	#define __M4RI_DEBUG_MZD		0
	#define __M4RI_HAVE_LIBPNG              0

	#define __M4RI_CC                       "clang"
	#define __M4RI_CFLAGS                   "  -g -O2"
	#define __M4RI_SIMD_CFLAGS              ""
	#define __M4RI_OPENMP_CFLAGS            ""

	// Helper macros.
	#define __M4RI_USE_MM_MALLOC		(__M4RI_HAVE_MM_MALLOC && __M4RI_HAVE_SSE2)
	#define __M4RI_USE_POSIX_MEMALIGN	(__M4RI_HAVE_POSIX_MEMALIGN && __M4RI_HAVE_SSE2)
	#define __M4RI_DD_QUIET			(0 && !0)

	#define __M4RI_ENABLE_MZD_CACHE         1
	#define __M4RI_ENABLE_MMC               1

	#include <math.h>
	#define LOG2(n) (log(n)/log(2))

#elif defined(iOS_M4RI)

	// Defines determined during configuration of m4ri.
	#define __M4RI_HAVE_MM_MALLOC		1
	#define __M4RI_HAVE_POSIX_MEMALIGN	0
	#define __M4RI_HAVE_SSE2		0
	#define __M4RI_HAVE_OPENMP		0
	#define __M4RI_CPU_L1_CACHE		32768
	#define __M4RI_CPU_L2_CACHE		262144
	#define __M4RI_CPU_L3_CACHE		262144
	#define __M4RI_DEBUG_DUMP		(0 || 0)
	#define __M4RI_DEBUG_MZD		0
	#define __M4RI_HAVE_LIBPNG              0

	#define __M4RI_CC                       "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang"
	#define __M4RI_CFLAGS                   "  -g -O2"
	#define __M4RI_SIMD_CFLAGS              ""
	#define __M4RI_OPENMP_CFLAGS            ""

	// Helper macros.
	#define __M4RI_USE_MM_MALLOC		(__M4RI_HAVE_MM_MALLOC && __M4RI_HAVE_SSE2)
	#define __M4RI_USE_POSIX_MEMALIGN	(__M4RI_HAVE_POSIX_MEMALIGN && __M4RI_HAVE_SSE2)
	#define __M4RI_DD_QUIET			(0 && !0)

	#define __M4RI_ENABLE_MZD_CACHE         1
	#define __M4RI_ENABLE_MMC               1

	#include <math.h>
	#define LOG2(n) (log(n)/log(2))

#elif defined(macOS_M4RI)

	// Defines determined during configuration of m4ri.
	#define __M4RI_HAVE_MM_MALLOC		1
	#define __M4RI_HAVE_POSIX_MEMALIGN	1
	#define __M4RI_HAVE_SSE2		1
	#define __M4RI_HAVE_OPENMP		0
	#define __M4RI_CPU_L1_CACHE		32768
	#define __M4RI_CPU_L2_CACHE		0
	#define __M4RI_CPU_L3_CACHE		0
	#define __M4RI_DEBUG_DUMP		(0 || 0)
	#define __M4RI_DEBUG_MZD		0
	#define __M4RI_HAVE_LIBPNG              0

	#define __M4RI_CC                       "gcc"
	#define __M4RI_CFLAGS                   " -mmmx -msse -msse2 -msse3  -g -O2"
	#define __M4RI_SIMD_CFLAGS              " -mmmx -msse -msse2 -msse3"
	#define __M4RI_OPENMP_CFLAGS            ""

	// Helper macros.
	#define __M4RI_USE_MM_MALLOC		(__M4RI_HAVE_MM_MALLOC && __M4RI_HAVE_SSE2)
	#define __M4RI_USE_POSIX_MEMALIGN	(__M4RI_HAVE_POSIX_MEMALIGN && __M4RI_HAVE_SSE2)
	#define __M4RI_DD_QUIET			(0 && !0)

	#define __M4RI_ENABLE_MZD_CACHE         1
	#define __M4RI_ENABLE_MMC               1

	#include <math.h>
	#define LOG2(n) (log(n)/log(2))

#else
	// Defines determined during configuration of m4ri.
	#define __M4RI_HAVE_MM_MALLOC		1
	#define __M4RI_HAVE_POSIX_MEMALIGN	0
	#define __M4RI_HAVE_SSE2		0
	#define __M4RI_HAVE_OPENMP		0
	#define __M4RI_CPU_L1_CACHE		32768
	#define __M4RI_CPU_L2_CACHE		262144
	#define __M4RI_CPU_L3_CACHE		262144
	#define __M4RI_DEBUG_DUMP		(0 || 0)
	#define __M4RI_DEBUG_MZD		0
	#define __M4RI_HAVE_LIBPNG              0

	#define __M4RI_CC                       "gcc"
	#define __M4RI_CFLAGS                   "  -g -O2"
	#define __M4RI_SIMD_CFLAGS              ""
	#define __M4RI_OPENMP_CFLAGS            ""

	// Helper macros.
	#define __M4RI_USE_MM_MALLOC		(__M4RI_HAVE_MM_MALLOC && __M4RI_HAVE_SSE2)
	#define __M4RI_USE_POSIX_MEMALIGN	(__M4RI_HAVE_POSIX_MEMALIGN && __M4RI_HAVE_SSE2)
	#define __M4RI_DD_QUIET			(0 && !0)

	#define __M4RI_ENABLE_MZD_CACHE         1
	#define __M4RI_ENABLE_MMC               1

	#include <math.h>
	#define LOG2(n) (log(n)/log(2))

#endif // defined
#endif // M4RI_M4RI_CONFIG_H
