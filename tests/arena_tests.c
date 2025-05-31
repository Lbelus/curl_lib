
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <criterion/criterion.h>
#include "../src/core/HTTP2/arena.h"
#include <fcntl.h>
#include <errno.h>
// // Writing a test with criterion example:
// // Test(suite_name, test_name)
// // {
// //     // write test here
// // }

Test(mem_alloc, ptr_alloc)
{
    arena_t arena = getarena();
    int *x = (int *)alloc(&arena, sizeof(int), _Alignof(int), 1);
    *x = 42;
    printf("Allocated int: %d\n", *x);
    cr_expect(*x == 42, "Expected \"ptr\" value to be 42.");
}

Test(load_file, load_file)
{
    arena_t arena = getarena();
    int fd = open("tests/files/simple_file.txt", O_RDONLY, 0644);
    if (fd == -1)
    {
        perror("Failed to open file");
        return;
    }
    split_t split = {0};
    split.tail = load_file(fd, &arena);
    slice_list_t* lines = getlines(split, &arena);
    printf("File content (FULL SPLIT): \n%s", split.tail.data);
    slice_list_t* node = lines;
    printf("File content (LINES):\n");
    while (node != NULL)
    {
        printf("#%i: %.*s\n", (int)node->item.len, (int)node->item.len, node->item.data);
        node = node->next;

    }
}
