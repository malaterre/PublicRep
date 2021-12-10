// Copyright Contributors to the OpenVDB Project
// SPDX-License-Identifier: MPL-2.0
///
/// @file Platform.h

#ifndef OPENVDB_PLATFORM_HAS_BEEN_INCLUDED
#define OPENVDB_PLATFORM_HAS_BEEN_INCLUDED

#define PRAGMA(x) _Pragma(#x)

/// @name Utilities
/// @{
/// @cond OPENVDB_VERSION_INTERNAL
#define OPENVDB_PREPROC_STRINGIFY_(x) #x
/// @endcond
/// @brief Return @a x as a string literal.  If @a x is a macro,
/// return its value as a string literal.
/// @hideinitializer
#define OPENVDB_PREPROC_STRINGIFY(x) OPENVDB_PREPROC_STRINGIFY_(x)

/// @cond OPENVDB_VERSION_INTERNAL
#define OPENVDB_PREPROC_CONCAT_(x, y) x ## y
/// @endcond
/// @brief Form a new token by concatenating two existing tokens.
/// If either token is a macro, concatenate its value.
/// @hideinitializer
#define OPENVDB_PREPROC_CONCAT(x, y) OPENVDB_PREPROC_CONCAT_(x, y)
/// @}

/// Macro for determining if GCC version is >= than X.Y
#if defined(__GNUC__)
    #define OPENVDB_CHECK_GCC(MAJOR, MINOR) \
        (__GNUC__ > MAJOR || (__GNUC__ == MAJOR && __GNUC_MINOR__ >= MINOR))
#else
    #define OPENVDB_CHECK_GCC(MAJOR, MINOR) 0
#endif

/// OpenVDB now requires C++11
#define OPENVDB_HAS_CXX11 1


/// SIMD Intrinsic Headers
#if defined(OPENVDB_USE_SSE42) || defined(OPENVDB_USE_AVX)
    #if defined(_WIN32)
        #include <intrin.h>
    #elif defined(__GNUC__)
        #if defined(__x86_64__) || defined(__i386__)
            #include <x86intrin.h>
        #elif defined(__ARM_NEON__)
            #include <arm_neon.h>
        #endif
    #endif
#endif

/// Windows defines
#ifdef _WIN32
    // Math constants are not included in <cmath> unless _USE_MATH_DEFINES is
    // defined on MSVC
    // https://docs.microsoft.com/en-us/cpp/c-runtime-library/math-constants
    #ifndef _USE_MATH_DEFINES
        #define _USE_MATH_DEFINES
    #endif
    ///Disable the non-portable Windows definitions of min() and max() macros
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif

    // By default, assume we're building OpenVDB as a DLL if we're dynamically
    // linking in the CRT, unless OPENVDB_STATICLIB is defined.
    #if defined(_DLL) && !defined(OPENVDB_STATICLIB) && !defined(OPENVDB_DLL)
        #define OPENVDB_DLL
    #endif

    // By default, assume that we're dynamically linking OpenEXR, unless
    // OPENVDB_OPENEXR_STATICLIB is defined.
    #if !defined(OPENVDB_OPENEXR_STATICLIB) && !defined(OPENEXR_DLL)
        #define OPENEXR_DLL
    #endif
#endif

/// Bracket code with OPENVDB_NO_UNREACHABLE_CODE_WARNING_BEGIN/_END,
/// as in the following example, to inhibit ICC remarks about unreachable code:
/// @code
/// template<typename NodeType>
/// void processNode(NodeType& node)
/// {
///     OPENVDB_NO_UNREACHABLE_CODE_WARNING_BEGIN
///     if (NodeType::LEVEL == 0) return; // ignore leaf nodes
///     int i = 0;
///     ...
///     OPENVDB_NO_UNREACHABLE_CODE_WARNING_END
/// }
/// @endcode
/// In the above, <tt>NodeType::LEVEL == 0</tt> is a compile-time constant expression,
/// so for some template instantiations, the line below it is unreachable.
#if defined(__INTEL_COMPILER)
    // Disable ICC remarks 111 ("statement is unreachable"), 128 ("loop is not reachable"),
    // 185 ("dynamic initialization in unreachable code"), and 280 ("selector expression
    // is constant").
    #define OPENVDB_NO_UNREACHABLE_CODE_WARNING_BEGIN \
        _Pragma("warning (push)") \
        _Pragma("warning (disable:111)") \
        _Pragma("warning (disable:128)") \
        _Pragma("warning (disable:185)") \
        _Pragma("warning (disable:280)")
    #define OPENVDB_NO_UNREACHABLE_CODE_WARNING_END \
        _Pragma("warning (pop)")
#elif defined(__clang__)
    #define OPENVDB_NO_UNREACHABLE_CODE_WARNING_BEGIN \
        PRAGMA(clang diagnostic push) \
        PRAGMA(clang diagnostic ignored "-Wunreachable-code")
    #define OPENVDB_NO_UNREACHABLE_CODE_WARNING_END \
        PRAGMA(clang diagnostic pop)
#else
    #define OPENVDB_NO_UNREACHABLE_CODE_WARNING_BEGIN
    #define OPENVDB_NO_UNREACHABLE_CODE_WARNING_END
#endif

/// Deprecation macros. Define OPENVDB_NO_DEPRECATION_WARNINGS to disable all
/// deprecation warnings in OpenVDB.
#ifndef OPENVDB_NO_DEPRECATION_WARNINGS
#define OPENVDB_DEPRECATED [[deprecated]]
#define OPENVDB_DEPRECATED_MESSAGE(msg) [[deprecated(msg)]]
#else
#define OPENVDB_DEPRECATED
#define OPENVDB_DEPRECATED_MESSAGE(msg)
#endif

/// @brief Bracket code with OPENVDB_NO_DEPRECATION_WARNING_BEGIN/_END,
/// to inhibit warnings about deprecated code.
/// @note Use this sparingly.  Remove references to deprecated code if at all possible.
/// @details Example:
/// @code
/// OPENVDB_DEPRECATED void myDeprecatedFunction() {}
///
/// {
///     OPENVDB_NO_DEPRECATION_WARNING_BEGIN
///     myDeprecatedFunction();
///     OPENVDB_NO_DEPRECATION_WARNING_END
/// }
/// @endcode
#if defined __INTEL_COMPILER
    #define OPENVDB_NO_DEPRECATION_WARNING_BEGIN \
        _Pragma("warning (push)") \
        _Pragma("warning (disable:1478)") \
        PRAGMA(message("NOTE: ignoring deprecation warning at " __FILE__  \
            ":" OPENVDB_PREPROC_STRINGIFY(__LINE__)))
    #define OPENVDB_NO_DEPRECATION_WARNING_END \
        _Pragma("warning (pop)")
#elif defined __clang__
    #define OPENVDB_NO_DEPRECATION_WARNING_BEGIN \
        _Pragma("clang diagnostic push") \
        _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
        // note: no #pragma message, since Clang treats them as warnings
    #define OPENVDB_NO_DEPRECATION_WARNING_END \
        _Pragma("clang diagnostic pop")
#elif defined __GNUC__
    #define OPENVDB_NO_DEPRECATION_WARNING_BEGIN \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"") \
        _Pragma("message(\"NOTE: ignoring deprecation warning\")")
    #define OPENVDB_NO_DEPRECATION_WARNING_END \
        _Pragma("GCC diagnostic pop")
#elif defined _MSC_VER
    #define OPENVDB_NO_DEPRECATION_WARNING_BEGIN \
        __pragma(warning(push)) \
        __pragma(warning(disable : 4996)) \
        __pragma(message("NOTE: ignoring deprecation warning at " __FILE__ \
            ":" OPENVDB_PREPROC_STRINGIFY(__LINE__)))
    #define OPENVDB_NO_DEPRECATION_WARNING_END \
        __pragma(warning(pop))
#else
    #define OPENVDB_NO_DEPRECATION_WARNING_BEGIN
    #define OPENVDB_NO_DEPRECATION_WARNING_END
#endif



/// Helper macros for defining library symbol visibility
#ifdef OPENVDB_EXPORT
#undef OPENVDB_EXPORT
#endif
#ifdef OPENVDB_IMPORT
#undef OPENVDB_IMPORT
#endif
#ifdef __GNUC__
    #define OPENVDB_EXPORT __attribute__((visibility("default")))
    #define OPENVDB_IMPORT __attribute__((visibility("default")))
#endif

#ifdef OPENVDB_API
#undef OPENVDB_API
#endif
#ifdef OPENVDB_PRIVATE
    #define OPENVDB_API OPENVDB_EXPORT
#else
    #define OPENVDB_API OPENVDB_IMPORT
#endif


#define OPENVDB_START_THREADSAFE_STATIC_REFERENCE
#define OPENVDB_FINISH_THREADSAFE_STATIC_REFERENCE
#define OPENVDB_START_THREADSAFE_STATIC_WRITE
#define OPENVDB_FINISH_THREADSAFE_STATIC_WRITE
#define OPENVDB_START_THREADSAFE_STATIC_ADDRESS
#define OPENVDB_FINISH_THREADSAFE_STATIC_ADDRESS

#define OPENVDB_START_NON_THREADSAFE_STATIC_REFERENCE
#define OPENVDB_FINISH_NON_THREADSAFE_STATIC_REFERENCE
#define OPENVDB_START_NON_THREADSAFE_STATIC_WRITE
#define OPENVDB_FINISH_NON_THREADSAFE_STATIC_WRITE
#define OPENVDB_START_NON_THREADSAFE_STATIC_ADDRESS
#define OPENVDB_FINISH_NON_THREADSAFE_STATIC_ADDRESS

#define OPENVDB_THREADSAFE_STATIC_REFERENCE(CODE) CODE
#define OPENVDB_THREADSAFE_STATIC_WRITE(CODE) CODE
#define OPENVDB_THREADSAFE_STATIC_ADDRESS(CODE) CODE


#endif // OPENVDB_PLATFORM_HAS_BEEN_INCLUDED
