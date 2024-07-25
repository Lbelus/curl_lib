#ifndef __USER_AGENT_HEADER_
#define __USER_AGENT_HEADER_


#ifdef __cplusplus
extern "C" {
#endif


#include <fcntl.h>
#include <my_parser.h>
#include <my_string.h>

char* pick_user_agent(char* designation);


// C readline helper
#ifdef __cplusplus
}
#endif

#endif