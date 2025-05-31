#include <fc_curl.h>

#include "./core/HTTP2/arena.h"
#include <fcntl.h>


int main(void)
{
    // uri_s_t uri = {0};
    // uri = init_fc_curl(uri, "https://www.google.com");
    // // url_p_s_t* url_s = uri.uri_union.url;
    // fc_curl(uri);
    // clean_fc_curl(uri);
    // test_allocation();

    arena_t arena = getarena();
    int fd = open("tests/files/simple_file.txt", O_RDONLY, 0644);
    load_file(fd, &arena);

    return EXIT_SUCCESS;
}
