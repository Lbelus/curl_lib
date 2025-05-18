#include "./arena.h"
#include <stdio.h>

arena_t getarena(void)
{
    static uint8_t mem[1<<16];
    arena_t arena = {0};
    arena.beg = mem;
    asm ("" : "+r"(arena.beg));  // launder the pointer
    arena.end = arena.beg + countof(mem);
    return arena;
}

void* alloc(arena_t* arena, ptrdiff_t size, ptrdiff_t align, ptrdiff_t count)
{
    ptrdiff_t padding = -(uintptr_t)arena->beg & (align - 1);
    ptrdiff_t available = arena->end - arena->beg - padding;
    if (available < 0 || count > available/size) {
        abort();  // one possible out-of-memory policy
    }
    void* ptr = arena->beg + padding;
    arena->beg += padding + count*size;
    return memset(ptr, 0, count*size);
}


int test_allocation()
{
    arena_t arena = getarena();

    int *x = (int *)alloc(&arena, sizeof(int), _Alignof(int), 1);
    *x = 42;

    printf("Allocated int: %d\n", *x);
    return EXIT_SUCCESS;
}

