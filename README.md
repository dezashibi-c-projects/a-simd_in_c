# Understanding SIMD: A Boost for C Programs

Single Instruction, Multiple Data, commonly known as SIMD, is a powerful computing technique that enables the simultaneous execution of the same operation on multiple data points. This approach can significantly enhance the performance of programs, particularly those dealing with large datasets or repetitive calculations. By leveraging SIMD, developers can write more efficient code that makes better use of modern CPU architectures.

SIMD is widely used in various domains where performance is critical. For instance, it plays a key role in multimedia processing, where large volumes of image or audio data need to be processed rapidly. Similarly, scientific simulations, which often involve repetitive mathematical operations on large datasets, can greatly benefit from SIMD. Even in gaming, where real-time processing of complex physics or graphics is required, SIMD can make a noticeable difference.

The concept behind SIMD is straightforward. Rather than executing the same instruction multiple times on individual pieces of data, SIMD allows a single instruction to operate on multiple data points simultaneously. This parallelism can lead to significant speed improvements, especially in tasks where the same operation needs to be performed repeatedly across large arrays of data.

Modern CPUs are designed with SIMD capabilities in mind. Various SIMD extensions, such as SSE (Streaming SIMD Extensions) and AVX (Advanced Vector Extensions), are available on x86 architectures, and these extensions provide specialized instructions that can handle multiple data points in a single instruction cycle. These instructions are typically executed using wider registers, allowing for more data to be processed simultaneously. For example, AVX can process 256 bits of data at once, which translates to handling eight 32-bit floating-point numbers in parallel.

Developers can take advantage of SIMD in C programming through several approaches. One common method is using intrinsics, which are special functions provided by the compiler that map directly to SIMD instructions. These intrinsics allow developers to write SIMD code without needing to delve into assembly language, making the process more accessible while still offering significant performance benefits.

**Intrinsics are special functions provided by the compiler that map directly to SIMD instructions. These functions are typically provided in header files like emmintrin.h for SSE2, immintrin.h for AVX, etc.**

```c
# include <emmintrin.h>

void add_vectors(float*a, float* b, float* c, int n) {
    for (int i = 0; i < n; i += 4) {
        __m128 va =_mm_loadu_ps(&a[i]);
        __m128 vb = _mm_loadu_ps(&b[i]);
        __m128 vc =_mm_add_ps(va, vb);
        _mm_storeu_ps(&c[i], vc);
    }
}
```

Another approach is to rely on the compiler's auto-vectorization capabilities. Modern compilers, such as GCC and Clang, can automatically identify opportunities to apply SIMD during the optimization process. By enabling the appropriate optimization flags, the compiler can transform standard loops into SIMD-optimized code, making it easier to benefit from SIMD without requiring manual intervention.

**Modern compilers can automatically vectorize code if optimization flags are enabled. For instance, using `-O2` or `-O3` with `gcc` or `clang`.**

SIMD can be particularly beneficial in scenarios where data alignment is managed correctly. Data should be aligned in memory to ensure optimal performance since many SIMD instructions require data to be aligned on specific boundaries, such as 16 or 32 bytes. Additionally, organizing data in a way that maximizes SIMD effectiveness, such as using structures of arrays rather than arrays of structures, can further enhance performance.

One of the challenges in utilizing SIMD is ensuring cross-platform compatibility. Different platforms support different SIMD extensions, so it's important to write code that can adapt to the available architecture. Preprocessor directives can be used to detect the platform and apply the appropriate SIMD instructions, ensuring that the program runs efficiently on various systems.

**An example of architecture determination for usage of `SIMD`**

```c
// Platform-specific SIMD headers
#if defined(__AVX__)
    #include <immintrin.h>
#elif defined(__SSE2__)
    #include <emmintrin.h>
#elif defined(_MSC_VER) && defined(_M_X64)
    #include <intrin.h>
#endif
```

SIMD is not only about improving performance; it's also about making efficient use of the underlying hardware. By leveraging SIMD, developers can unlock the full potential of modern CPUs, reducing execution times and improving the responsiveness of their applications. Whether you're working on a scientific simulation, a multimedia application, or a game, SIMD can help you achieve better performance and make your C programs more competitive in terms of speed and efficiency.

Generally speaking, SIMD is a valuable tool in the arsenal of any C programmer aiming to optimize performance. By understanding the principles of SIMD and how to apply them in a cross-platform context, developers can create more efficient and responsive applications that take full advantage of modern hardware capabilities. As you continue to explore and implement SIMD in your projects, you'll likely find that the effort pays off in terms of both speed and efficiency, making your programs more capable of handling the demands of today's data-intensive tasks.

## Example Code

The [C program that is provided in the repository](/simd_example.c) uses SIMD to add two arrays of floating-point numbers. We'll use different SIMD instructions based on the platform and available SIMD extensions (e.g., SSE for x86 architecture).

**I've tested the program with both `zig cc` and `gcc` using `-O3` on Windows and WSL.**

The output in my system is like this:

``` plain
AVX is detected.
c[0] = 1024.000000
c[1] = 1024.000000
c[2] = 1024.000000
c[3] = 1024.000000
c[4] = 1024.000000
c[5] = 1024.000000
c[6] = 1024.000000
c[7] = 1024.000000
c[8] = 1024.000000
c[9] = 1024.000000
```

## License

This project is licensed under the Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0) License.

You are free to:

- Share — copy and redistribute the material in any medium or format
- Adapt — remix, transform, and build upon the material

Under the following terms:

- Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
- NonCommercial — You may not use the material for commercial purposes.

No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.

For more details, refer to the [LICENSE](./LICENSE) file.

### Author

Navid Dezashibi  
<navid@dezashibi.com>
