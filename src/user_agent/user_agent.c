#include <my_user_agent.h>


char* pick_user_agent(char* designation)
{
    char*   str      = NULL;
    char*   result   = NULL;
    int     pos      = 0;
	int     fd       = 0;
    fd = open("./user_agents/user_agents.txt", O_RDONLY, 400);
    init_my_readline();
	while ((str = my_readline(fd)) != NULL)
	{
        if (my_strstr(str, designation) != NULL)
        {
            pos = find_ch(str, '=');
            str[pos] = '\0';
            result = my_strdup(&str[pos + 1]);
            fd = -1;
        }
        free(str);
	}
	flush_buffer();
	return result;
}