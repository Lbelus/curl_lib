#ifndef __CURL_API_H_
#define __CURL_API_H_

#include <main_header.h>
#include <my_linkedlist.h>
#include <my_user_agent.h>
#include <my_uri_structs.h>
#include <my_cookie_jar.h>
#include <my_payload.h>

#ifdef __cplusplus
extern "C" {
#endif



node_t* login(char* username, char* password, char* user_agent_designation, char* url);
    node_t* get_session_cookie(char* user_agent, char* user_agent_designation, char* url);
    node_t* get_auth_cookie(char* user_agent, char* user_agent_designation, char* cookies, char* payload, char* url);
    node_t* get_cookie(url_p_s_t*  url_s);

#ifdef __cplusplus
}
#endif

#endif