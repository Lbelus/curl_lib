#ifndef __PARSER_HEADERFILE_
#define __PARSER_HEADERFILE_

#include <main_header.h>
#include <openssl/ssl.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_INPUT_TOKENS  1000
#define PROTOCOL_SEP      "://"
#define _HTTPS__          "https://"
#define _HTTPS_LEN_       8
#define _HTTP__           "http://"
#define _HTTP_LEN_        7
#define PATH_SEP          '/'

char* set_var(char* src, int len);
// char* create_get_request(char* path, char* domain, int total_str_len);
url_p_s_t* my_url_parser(char* url);
void free_url_struct(url_p_s_t* url_s);
protocol_enum get_protocol_from_url(char* url);


int token_array_size(char** resp_tokens);
char* set_response_code(char* response);

char* init_my_readline();
char* my_readline(int fd);
char* my_SSL_readline(SSL* ssl);
void flush_buffer();

#ifdef __cplusplus
}
#endif

#endif