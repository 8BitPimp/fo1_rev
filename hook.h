#pragma once

// Simple function hooker, inserts a rel32 JMP at 'from' branching to 'to'
void hook(void * from, void * to);
