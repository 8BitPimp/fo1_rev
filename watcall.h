#pragma once
#include <stdint.h>

// Call watcom function, 0 arguments
template <uint32_t offset>
void watcall() {
    static const void * dst = (const void *) offset;
    __asm call dst
}

// Call watcom function, 0 arguments, returns
template <typename ret_type,
          uint32_t offset>
ret_type watcall() {
    static const void * dst = (const void *) offset;
    ret_type ret_val;
    __asm call dst
    __asm mov ret_val, eax
    return ret_val;
}

// Call watcom function, 1 argument
template <uint32_t offset,
          typename type_a>
void watcall(type_a a) {
    static const void * dst = (const void *) offset;
    __asm mov eax, a
    __asm call dst
}

// Call watcom function, 1 argument, returns
template <typename ret_type,
          uint32_t offset,
          typename type_a>
ret_type watcall(type_a a) {
    static const void * dst = (const void *) offset;
    ret_type ret_val;
    __asm mov eax, a
    __asm call dst
    __asm mov ret_val, eax
    return ret_val;
}

// Call watcom function, 2 arguments
template <uint32_t offset,
          typename type_a,
          typename type_b>
void watcall(type_a a, type_b b) {
    static const void * dst = (const void *) offset;
    __asm mov eax, a
    __asm mov edx, b
    __asm call dst
}

// Call watcom function, 2 arguments, returns
template <typename ret_type,
          uint32_t offset,
          typename type_a,
          typename type_b>
ret_type watcall(type_a a, type_b b) {
    static const void * dst = (const void *) offset;
    ret_type ret_val;
    __asm mov eax, a
    __asm mov edx, b
    __asm call dst
    __asm mov ret_val, eax
    return ret_val;
}

// Call watcom function, 3 arguments
template <uint32_t offset,
          typename type_a,
          typename type_b,
          typename type_c>
void watcall(type_a a, type_b b, type_c c) {
    static const void * dst = (const void *) offset;
    __asm mov eax, a
    __asm mov edx, b
    __asm mov ebx, c
    __asm call dst
}

// Call watcom function, 3 arguments, returns
template <typename ret_type,
          uint32_t offset,
          typename type_a,
          typename type_b,
          typename type_c>
ret_type watcall(type_a a, type_b b, type_c c) {
    static const void * dst = (const void *) offset;
    ret_type ret_val;
    __asm mov eax, a
    __asm mov edx, b
    __asm mov ebx, c
    __asm call dst
    __asm mov ret_val, eax
    return ret_val;
}

// Call watcom function, 4 arguments
template <uint32_t offset,
          typename type_a,
          typename type_b,
          typename type_c,
          typename type_d>
void watcall(type_a a, type_b b, type_c c, type_d d) {
    static const void * dst = (const void *) offset;
    __asm mov eax, a
    __asm mov edx, b
    __asm mov ebx, c
    __asm mov ecx, d
    __asm call dst
}

// Call watcom function, 4 arguments, returns
template <typename ret_type,
          uint32_t offset,
          typename type_a,
          typename type_b,
          typename type_c,
          typename type_d>
ret_type watcall(type_a a, type_b b, type_c c, type_d d) {
    static const void * dst = (const void *) offset;
    ret_type ret_val;
    __asm mov eax, a
    __asm mov edx, b
    __asm mov ebx, c
    __asm mov ecx, d
    __asm call dst
    __asm mov ret_val, eax
    return ret_val
}
