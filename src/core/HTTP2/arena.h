#ifndef __ARENA_H_
#define __ARENA_H_

#include <stddef.h>
#include <stdlib.h> // abort() need to find another way to exit() program.
#include <unistd.h>

#include <stdint.h>
#include <string.h>
#include <errno.h>


#ifndef __SLICE_S_
#define __SLICE_S_
struct slice_s
{
    uint8_t* data;
    ptrdiff_t len;
};
typedef struct slice_s slice_t;
#endif

#ifndef __SLICE_LIST_S_
#define __SLICE_LIST_S_
struct slice_list_s
{
    struct slice_list_s* next;
    slice_t item;
};
typedef struct slice_list_s slice_list_t;
#endif

#ifndef __SPLIT_S_
#define __SPLIT_S_
struct split_s
{
    slice_t head;
    slice_t tail;
};
typedef struct split_s split_t;
#endif

#ifndef __ARENA_S_
#define __ARENA_S_
struct arena_s
{
    uint8_t* base;
    uint8_t* beg;
    uint8_t* end;
};
typedef struct arena_s arena_t;
#endif


// conn_arena
// 
// stream_arena
//
// global_arena
//
// scratch

arena_t getarena(void);
void*   alloc(arena_t* arena, ptrdiff_t size, ptrdiff_t align, ptrdiff_t count);
void    arena_reset(arena_t* arena);

slice_t load_file(int fd, arena_t* arena);
slice_list_t* getlines(split_t split, arena_t* permanent);

// right newN based on number of arguments
#define new(...)            newx(__VA_ARGS__, new4, new3, new2)(__VA_ARGS__)
#define newx(a,b,c,d,e,...) e
// Core implementation
#define new2(a, t)          (t *)alloc(a, sizeof(t), __alignof__(t), 1)
#define new3(a, t, n)       (t *)alloc(a, sizeof(t), __alignof__(t), n)
#define countof(a) (ptrdiff_t)(sizeof(a) / sizeof(*(a)))

#endif
