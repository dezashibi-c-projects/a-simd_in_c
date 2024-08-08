// ***************************************************************************************
//    Project: Understanding SIMD: A Boost for C Programs
//    File: simd_example.c
//    Date: 2024-08-08
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https://www.dezashibi.com | https://github.com/dezashibi
//    License:
//     Please refer to the LICENSE file, repository or website for more information about
//     the licensing of this work. If you have any questions or concerns,
//     please feel free to contact me at the email address provided above.
// ***************************************************************************************
// *  Description: Please refer to the readme file
// ***************************************************************************************

#include <stdio.h>
#include <stdlib.h>

// Platform-specific SIMD headers
#if defined(__AVX__)
#include <immintrin.h>
#elif defined(__SSE2__)
#include <emmintrin.h>
#elif defined(_MSC_VER) && defined(_M_X64)
#include <intrin.h>
#endif

// SIMD-based array addition
void add_arrays_simd(float* a, float* b, float* c, size_t n)
{
#if defined(__AVX__)
    puts("AVX is detected.");

    size_t i;
    for (i = 0; i + 8 <= n; i += 8)
    {
        __m256 va = _mm256_loadu_ps(&a[i]);
        __m256 vb = _mm256_loadu_ps(&b[i]);
        __m256 vc = _mm256_add_ps(va, vb);
        _mm256_storeu_ps(&c[i], vc);
    }
    // Process remaining elements
    for (; i < n; ++i)
    {
        c[i] = a[i] + b[i];
    }
#elif defined(__SSE2__)
    puts(SSE2 "is detected.");

    size_t i;
    for (i = 0; i + 4 <= n; i += 4)
    {
        __m128 va = _mm_loadu_ps(&a[i]);
        __m128 vb = _mm_loadu_ps(&b[i]);
        __m128 vc = _mm_add_ps(va, vb);
        _mm_storeu_ps(&c[i], vc);
    }
    // Process remaining elements
    for (; i < n; ++i)
    {
        c[i] = a[i] + b[i];
    }
#else
    // Fallback to scalar addition if SIMD is not available
    puts("no SIMD extension is detected.");
    for (size_t i = 0; i < n; ++i)
    {
        c[i] = a[i] + b[i];
    }
#endif
}

// Helper function to initialize arrays
void initialize_arrays(float* a, float* b, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        a[i] = (float)i;
        b[i] = (float)(n - i);
    }
}

int main()
{
    size_t n = 1024; // Array size
    float* a = (float*)malloc(n * sizeof(float));
    float* b = (float*)malloc(n * sizeof(float));
    float* c = (float*)malloc(n * sizeof(float));

    if (!a || !b || !c)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    initialize_arrays(a, b, n);

    add_arrays_simd(a, b, c, n);

    // Print the first 10 results for verification
    for (size_t i = 0; i < 10; ++i)
    {
        printf("c[%zu] = %f\n", i, c[i]);
    }

    free(a);
    free(b);
    free(c);

    return 0;
}
