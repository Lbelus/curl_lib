// #include <main_header.h>
#include <curl_api.h>

int main(void)
{
    node_t* cookie_jar = login("useName", "passWord", "ANDROID OS", "https://www.linkedin.com/uas/authenticate");
    free_llist(cookie_jar);
    return EXIT_SUCCESS;
}