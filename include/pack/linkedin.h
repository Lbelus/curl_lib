#ifndef __LINKEDIN_API_H_
#define __LINKEDIN_API_H_

#include <main_header.h>
#include <my_linkedlist.h>
#include <my_user_agent.h>
#include <my_uri_structs.h>
#include <my_cookie_jar.h>
#include <my_payload.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LIN_AUTH_ADDR       "https://www.linkedin.com/uas/authenticate"
#define LIN_USER_ADDR       "https://www.linkedin.com/voyager/api/identity/profiles/"
#define LIN_USERSKILL       "/skills?count="
#define LIN_EXPERIENCES     "/positions"
#define LIN_EDUCATION       "/educationView"
#define LIN_PROFILE         "/profileView"
#define LIN_PAGINATION      "&start="
#define LIN_VIEWCOUNT_ADDR  "https://www.linkedin.com/voyager/api/identity/wvmpCards"
#define LIN_ORG_ADDR        "https://www.linkedin.com/voyager/api/organization/company/"
#define LIN_ORG_ABOUT       "/about"


node_t* login(char* username, char* password, char* user_agent_designation);
    node_t* get_session_cookie(char* user_agent, char* user_agent_designation);
    node_t* get_auth_cookie(char* user_agent, char* user_agent_designation,char* cookies, char* payload);
    node_t* get_cookie(url_p_s_t*  url_s);


void get_user_skills(node_t* cookie_jar, char* username, char* user_agent_designation);
void get_user_experience(node_t* cookie_jar, char* username, char* user_agent_designation);
void get_user_education(node_t* cookie_jar, char* username, char* user_agent_designation);
void get_user_profile(node_t* cookie_jar, char* username, char* user_agent_designation);

void get_view_count(node_t* cookie_jar, char* user_agent_designation);
void get_about_organization(node_t* cookie_jar, char* organization_name, char* user_agent_designation);

#ifdef __cplusplus
}
#endif
// int     build_payload();
// int     authenticate();
// int     fetch_metadata();

#endif