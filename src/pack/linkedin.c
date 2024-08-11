#include <linkedin_api.h>

node_t* login(char* username, char* password, char* user_agent_designation)
{
    node_t* cookie_jar = NULL;
    char* user_agent = pick_user_agent(user_agent_designation);
    cookie_jar = get_session_cookie(user_agent, user_agent_designation);
    char* csrf_token = get_csrf_token(cookie_jar);
    char* payload = set_auth_payload(username, password, csrf_token);
    char* cookies_str = set_cookies_str(cookie_jar);
    free_llist(cookie_jar);
    printf("cookies: %s\n", cookies_str);
    printf("payload %s\n", payload);
    cookie_jar = get_auth_cookie(user_agent, user_agent_designation, cookies_str, payload);
    free(cookies_str);
    printf("got cookie_jar\n");
    free(user_agent);
    free(payload);
    return cookie_jar;
}

url_p_s_t* set_parsed_url_struct(char* url)
{
    uri_s_t uri;
    uri = init_my_curl(uri, url);
    url_p_s_t* url_s = uri.uri_union.url;
    return url_s;
}

node_t* get_session_cookie(char* user_agent, char* user_agent_designation)
{
    node_t* cookie_jar = NULL;
    url_p_s_t* url_s = set_parsed_url_struct(LIN_AUTH_ADDR);
    char* user_a_str = msg_user_agent(user_agent, user_agent_designation);
  	url_s->req = create_user_a_get_request_(url_s->path, url_s->domain, user_a_str);
    cookie_jar = get_cookie(url_s);
    return cookie_jar;
}

node_t* get_auth_cookie(char* user_agent, char* user_agent_designation, char* cookies, char* payload)
{
    node_t* cookie_jar = NULL;
    url_p_s_t* url_s = set_parsed_url_struct(LIN_AUTH_ADDR);
    printf("host:%s, path:%s\n", url_s->path, url_s->domain);
    char* host_path     = msg_path_host(POST_MSG_P1,url_s->path, url_s->domain);
    char* user_a_str    = msg_user_agent(user_agent, user_agent_designation);
    char* payload_str   = msg_payload(cookies, payload);
    url_s->req          = create_auth_request(host_path, user_a_str, payload_str);
    printf("\n\n\nrequest:\n%s\n\n\n", url_s->req);
    cookie_jar = get_cookie(url_s);
    return cookie_jar;
}

node_t* get_cookie(url_p_s_t*  url_s)
{
    node_t* cookie_jar = NULL;
    cookie_jar = req_cookie(url_s->domain, url_s->req);
    free_url_struct(url_s);
    return cookie_jar;
}

    //  "https://www.linkedin.com/voyager/api/identity/profiles/$PROFILE_ID/skills?count=100&start=0"
char* build_user_skill_url(char* username)
{
	char* msg = NULL;
	msg = concat_string(6, 
		LIN_USER_ADDR,
		username,
		LIN_USERSKILL,
		"100",
        LIN_PAGINATION,
        "0"
	);
    return msg;
}

void get_user_skills(node_t* cookie_jar, char* username, char* user_agent_designation)
{
    char* user_agent    = pick_user_agent(user_agent_designation);
    char* csrf_token    = get_csrf_token(cookie_jar);
    char* url           = build_user_skill_url(username);
    url_p_s_t* url_s    = set_parsed_url_struct(url);
    char* host_path     = msg_path_host(GET_MSG_P1, url_s->path, url_s->domain);
    char* user_a_str    = msg_user_agent(user_agent, user_agent_designation);
    char* cookies_str   = set_cookies_str(cookie_jar);
    char* cookie_msg    = msg_cookie(cookies_str, csrf_token);
    url_s->req          = create_auth_request(host_path, user_a_str, cookie_msg);
    printf("\n\n\nrequest:\n%s\n\n\n", url_s->req);
    perform_get_request(url_s->domain, url_s->req, url_s->protocol);
    free_url_struct(url_s);
    free(user_agent);
    free(cookies_str);
    free(url);
}

// "https://www.linkedin.com/voyager/api/identity/wvmpCards"

void get_view_count(node_t* cookie_jar, char* user_agent_designation)
{
    char* user_agent    = pick_user_agent(user_agent_designation);
    char* csrf_token    = get_csrf_token(cookie_jar);
    url_p_s_t* url_s    = set_parsed_url_struct(LIN_VIEWCOUNT_ADDR);
    char* host_path     = msg_path_host(GET_MSG_P1, url_s->path, url_s->domain);
    char* user_a_str    = msg_user_agent(user_agent, user_agent_designation);
    char* cookies_str   = set_cookies_str(cookie_jar);
    char* cookie_msg    = msg_cookie(cookies_str, csrf_token);
    url_s->req          = create_auth_request(host_path, user_a_str, cookie_msg);
    printf("\n\n\nrequest:\n%s\n\n\n", url_s->req);
    perform_get_request(url_s->domain, url_s->req, url_s->protocol);
    free_url_struct(url_s);
    free(user_agent);
    free(cookies_str);
}

//  "https://www.linkedin.com/voyager/api/organization/$ORGANIZATION_ID/about" does not work :/

char* build_about_org_url(char* organization_name)
{
	char* msg = NULL;
	msg = concat_string(3, 
        LIN_ORG_ADDR,
        organization_name,
        LIN_ORG_ABOUT
	);
    return msg;
}

void get_about_organization(node_t* cookie_jar, char* organization_name, char* user_agent_designation)
{
    char* user_agent    = pick_user_agent(user_agent_designation);
    char* csrf_token    = get_csrf_token(cookie_jar);
    char* url           = build_about_org_url(organization_name);
    url_p_s_t* url_s    = set_parsed_url_struct(url);
    char* host_path     = msg_path_host(GET_MSG_P1, url_s->path, url_s->domain);
    char* user_a_str    = msg_user_agent(user_agent, user_agent_designation);
    char* cookies_str   = set_cookies_str(cookie_jar);
    char* cookie_msg    = msg_cookie(cookies_str, csrf_token);
    url_s->req          = create_auth_request(host_path, user_a_str, cookie_msg);
    printf("\n\n\nrequest:\n%s\n\n\n", url_s->req);
    perform_get_request(url_s->domain, url_s->req, url_s->protocol);
    free_url_struct(url_s);
    free(user_agent);
    free(cookies_str);
    free(url);
}

char* build_user_experience_url(char* username)
{
	char* msg = NULL;
	msg = concat_string(3, 
		LIN_USER_ADDR,
		username,
		LIN_EXPERIENCES
	);
    return msg;
}

// "https://www.linkedin.com/voyager/api/identity/profiles/$URN_ID || $USERNAME/positions"

void get_user_experience(node_t* cookie_jar, char* username, char* user_agent_designation)
{
    char* user_agent    = pick_user_agent(user_agent_designation);
    char* csrf_token    = get_csrf_token(cookie_jar);
    char* url           = build_user_experience_url(username);
    url_p_s_t* url_s    = set_parsed_url_struct(url);
    char* host_path     = msg_path_host(GET_MSG_P1, url_s->path, url_s->domain);
    char* user_a_str    = msg_user_agent(user_agent, user_agent_designation);
    char* cookies_str   = set_cookies_str(cookie_jar);
    char* cookie_msg    = msg_cookie(cookies_str, csrf_token);
    url_s->req          = create_auth_request(host_path, user_a_str, cookie_msg);
    printf("\n\n\nrequest:\n%s\n\n\n", url_s->req);
    perform_get_request(url_s->domain, url_s->req, url_s->protocol);
    free_url_struct(url_s);
    free(user_agent);
    free(cookies_str);
    free(url);
}


char* build_user_education_url(char* username)
{
	char* msg = NULL;
	msg = concat_string(3, 
		LIN_USER_ADDR,
		username,
		LIN_EDUCATION
	);
    return msg;
}

void get_user_education(node_t* cookie_jar, char* username, char* user_agent_designation)
{
    char* user_agent    = pick_user_agent(user_agent_designation);
    char* csrf_token    = get_csrf_token(cookie_jar);
    char* url           = build_user_education_url(username);
    url_p_s_t* url_s    = set_parsed_url_struct(url);
    char* host_path     = msg_path_host(GET_MSG_P1, url_s->path, url_s->domain);
    char* user_a_str    = msg_user_agent(user_agent, user_agent_designation);
    char* cookies_str   = set_cookies_str(cookie_jar);
    char* cookie_msg    = msg_cookie(cookies_str, csrf_token);
    url_s->req          = create_auth_request(host_path, user_a_str, cookie_msg);
    printf("\n\n\nrequest:\n%s\n\n\n", url_s->req);
    perform_get_request(url_s->domain, url_s->req, url_s->protocol);
    free_url_struct(url_s);
    free(user_agent);
    free(cookies_str);
    free(url);
}


char* build_user_profile_url(char* username)
{
	char* msg = NULL;
	msg = concat_string(3, 
		LIN_USER_ADDR,
		username,
		LIN_PROFILE
	);
    return msg;
}

// "https://www.linkedin.com/voyager/api/identity/profiles/$URN_ID || $USERNAME/profileView"

void get_user_profile(node_t* cookie_jar, char* username, char* user_agent_designation)
{
    char* user_agent    = pick_user_agent(user_agent_designation);
    char* csrf_token    = get_csrf_token(cookie_jar);
    char* url           = build_user_profile_url(username);
    url_p_s_t* url_s    = set_parsed_url_struct(url);
    char* host_path     = msg_path_host(GET_MSG_P1, url_s->path, url_s->domain);
    char* user_a_str    = msg_user_agent(user_agent, user_agent_designation);
    char* cookies_str   = set_cookies_str(cookie_jar);
    char* cookie_msg    = msg_cookie(cookies_str, csrf_token);
    url_s->req          = create_auth_request(host_path, user_a_str, cookie_msg);
    printf("\n\n\nrequest:\n%s\n\n\n", url_s->req);
    perform_get_request(url_s->domain, url_s->req, url_s->protocol);
    free_url_struct(url_s);
    free(user_agent);
    free(cookies_str);
    free(url);
}