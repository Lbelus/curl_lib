#ifndef __ARENA_H_
#define __ARENA_H_

#include <stddef.h>
#include <stdlib.h> // abort() need to find another way to exit() program.

#include <stdint.h>
#include <string.h>

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
struct slice_pair_s
{
    slice_t base;
    slice_t current;
    slice_t tail;
};
typedef struct split_s splice_t;
#endif

#ifndef __ARENA_S_
#define __ARENA_S_
struct arena_s
{
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



// right newN based on number of arguments
#define new(...)            newx(__VA_ARGS__, new4, new3, new2)(__VA_ARGS__)
#define newx(a,b,c,d,e,...) e
// Core implementation
#define new2(a, t)          (t *)alloc(a, sizeof(t), alignof(t), 1, 0)
#define new3(a, t, n)       (t *)alloc(a, sizeof(t), alignof(t), n, 0)
#define new4(a, t, n, f)    (t *)alloc(a, sizeof(t), alignof(t), n, f)

#define countof(a) (ptrdiff_t)(sizeof(a) / sizeof(*(a)))

int test_allocation();

#endif
