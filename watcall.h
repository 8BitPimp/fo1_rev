#pragma once
#include <stdint.h>

// Call watcom function, 0 arguments
template <uint32_t offset,
          typename ret_type>
ret_type watcall() {
    static const char * dst = (const char *) offset;
    ret_type ret_val;
    __asm call dst
    __asm mov ret_val, eax
    return ret_val;
}

// Call watcom function, 1 argument
template <uint32_t offset,
          typename ret_type,
          typename type_a>
ret_type watcall(type_a a) {
    static const char * dst = (const char *) offset;
    ret_type ret_val;
    __asm mov eax, a
    __asm call dst
    __asm mov ret_val, eax
    return ret_val;
}

// Call watcom function, 2 arguments
template <uint32_t offset,
          typename ret_type,
          typename type_a,
          typename type_b>
ret_type watcall(type_a a, type_b b) {
    static const char * dst = (const char *) offset;
    ret_type ret_val;
    __asm mov eax, a
    __asm mov edx, b
    __asm call dst
    __asm mov ret_val, eax
    return ret_val;
}

// Call watcom function, 3 arguments
template <uint32_t offset,
          typename ret_type,
          typename type_a,
          typename type_b,
          typename type_c>
ret_type watcall(type_a a, type_b b, type_c c) {
    static const char * dst = (const char *) offset;
    ret_type ret_val;
    __asm mov eax, a
    __asm mov edx, b
    __asm mov ecx, c
    __asm call dst
    __asm mov ret_val, eax
    return ret_val;\
}

// Call watcom function, 4 arguments
template <uint32_t offset,
          typename ret_type,
          typename type_a,
          typename type_b,
          typename type_c,
          typename type_d>
ret_type watcall(type_a a, type_b b, type_c c, type_d d) {
    static const char * dst = (const char *) offset;
    ret_type ret_val;
    __asm mov eax, a
    __asm mov edx, b
    __asm mov ecx, c
    __asm mov edx, d
    __asm call dst
    __asm mov ret_val, eax
    return ret_val
}
