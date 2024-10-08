#ifndef _MY_PAYLOAD_H_
#define _MY_PAYLOAD_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <my_linkedlist.h>
#include <my_string.h>
#include <my_cookie_jar.h>
#include <my_curl_header.h>

// #ifndef _PAYLOAD_S_
// #define _PAYLOAD_S_
// struct payload_s
// {
//     char*   username;
//     char*   password;
//     char*   csrf_token;
//     int     username_len;
//     int     password_len;
//     int     csrf_token_len;
// };
// typedef struct payload_s payload_t;
// #endif

#define __AJAX_STR_         "JSESSIONID"
#define PAYLOAD_USERN       "session_key="
#define PAYLOAD_PASSW       "&session_password="
#define PAYLOAD_SESSI       "&JSESSIONID="
#define PAYLOAD_BASE_LEN    42

char*       get_csrf_token(node_t* head);
char*       set_auth_payload(char* username, char* password, char* csrf_token);
// payload_t*  create_payload_struct(char* user, char* password, char* csrf_token);
char*       concat_string(int argc, ...);

#ifdef __cplusplus
}
#endif

#endif