#ifndef __USER_AGENT_HEADER_
#define __USER_AGENT_HEADER_


#ifdef __cplusplus
extern "C" {
#endif


#include <fcntl.h>
#include <my_parser.h>
#include <my_string.h>


#ifndef _USER_AGENT_STRUCT_
#define _USER_AGENT_STRUCT_
struct user_agent_s
{
    char* designation;
    char* value
};
typedef struct user_agent_s user_agent_t; 
#endif


user_agent_t*   pick_user_agent(char* designation);
user_agent_t*   set_user_agent(char* designation, char* value);
int             free_user_agent(user_agent_t* user_agent);

// C readline helper
#ifdef __cplusplus
}
#endif

#endif