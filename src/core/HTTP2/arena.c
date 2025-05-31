#include "./arena.h"
#include <stdio.h>

arena_t getarena(void)
{
    static uint8_t mem[1<<16];
    arena_t arena = {0};
    arena.beg = mem;
    asm ("" : "+r"(arena.beg));  // launder the pointer
    arena.base = arena.beg;
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


void arena_reset(arena_t* arena)
{
    arena->beg = arena->base;
}


split_t create_split(slice_t slice, ptrdiff_t index, uint8_t* tail_pos, ptrdiff_t tail_len)
{
    split_t split   = {0};
    split.head.data = slice.data;
    split.head.len  = index;
    split.tail.data = tail_pos;
    split.tail.len  = tail_len;
    return split;
}

split_t cut_line(slice_t slice, char delimiter)
{
    ptrdiff_t index = 0;
    split_t split = {0};
    while (index != slice.len)
    {
        if (slice.data[index] == delimiter)
        {
            uint8_t* tail_pos = slice.data + index + 1;
            ptrdiff_t tail_len = slice.len - index - 1;
            split = create_split(slice, index, tail_pos, tail_len);
            return split;
        }
        index += 1;
    }
    uint8_t* tail_pos = slice.data + slice.len;
    split = create_split(slice, index, tail_pos, 0);
    return split;
}

slice_t load_file(int fd, arena_t* arena)
{
    uint8_t* file_start = arena->beg;
    size_t byte_count = 0;
    size_t read_size = 512;
    char* buff = new(arena, char, read_size);
    while ((byte_count = read(fd, buff, read_size)) != 0)
    {
        if (byte_count == -1)
        {
            perror("Load_file read has failed:");
        }
        buff = new(arena, char, read_size);
    }
    arena->beg -= read_size - byte_count;
    slice_t file_data = 
    {
        .data = file_start,
        .len = arena->beg - file_start
    };
    return file_data;
}

slice_list_t* getlines(split_t split, arena_t* permanent)
{
    slice_list_t* head = NULL;
    slice_list_t** tail = &head;
    while (split.tail.len)
    {
        split = cut_line(split.tail, '\n');
        *tail = new(permanent, slice_list_t, 1);
        (*tail)->item = split.head;
        tail = &(*tail)->next;
    }
    return head;
}

// int test_allocation()
// {
//     arena_t arena = getarena();

//     int *x = (int *)alloc(&arena, sizeof(int), _Alignof(int), 1);
//     *x = 42;

//     printf("Allocated int: %d\n", *x);
//     return EXIT_SUCCESS;
// }

