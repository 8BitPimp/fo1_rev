#pragma once
#include <stdint.h>

// Simple function hooker, inserts a rel32 JMP at 'from' branching to 'to'
void hook(void * from, void * to);

// Simple code/memory patch routine
void patch(void * pos, void * data, uint32_t size);

//
void nop(uint32_t offset, uint32_t size);
