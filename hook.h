#pragma once
#include <stdint.h>
#include <string.h>

// Simple function hooker, inserts a rel32 JMP at 'from' branching to 'to'
void hook(void * from, void * to);

// Simple code/memory patch routine
void patch(void * pos, void * data, uint32_t size);

//
void nop(uint32_t offset, uint32_t size);

// Read memory from an offset
template <typename type_t>
type_t read(uint32_t offset) {
    type_t val = 0;
    memcpy(&val, (void*)offset, sizeof(type_t));
    return val;
}

// Write memory to an offset
template <typename type_t>
void write(uint32_t offset, type_t val) {
    memcpy( (void*) offset, &val, sizeof(type_t));
}

// Copy memory between two offsets
template <typename type_t>
void copy(uint32_t from, uint32_t to) {
    memcpy((void*) to, (void*) from, sizeof(type_t));
}
