#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

int all_n(char *s)
{
	while (*s)
	{
		if (*s != 'n')
			return (0);
		s++;
	}
	return (1);
}

void ft_cmd_echo(char **arg)
{
    int i = 0;
    int new_line = 1;

    while (arg[i] && arg[i][0] == '-' && arg[i][1] == 'n' && all_n(arg[i] + 1))
    {
        new_line = 0;
        i++;
    }
    while (arg[i])
    {
        char *str = arg[i];
        int j = 0;

        if ((str[0] == '\'' && str[strlen(str) - 1] == '\'') || (str[0] == '\"' && str[strlen(str) - 1] == '\"'))
        {
            str[strlen(str) - 1] = '\0'; 
            str++;
        }
        printf(CYAN "%s" RESET, str);
        if (arg[i + 1])
            printf(" ");
        i++;
    }
    if (new_line)
        printf("\n");
}

void ft_cmd_cd(char **arg)
{
    static char prev_dir[PATH_MAX] = "";
    const char *last = NULL;
    char curr_dir[PATH_MAX];

    if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
    {
        perror("shell error");
        return;
    }
	if (arg[0] == NULL)
		return ;
	else if (arg[0] && strcmp(arg[0], "~") == 0)
	{
		last = getenv("HOME");
        if (!last)
		{
			printf("her is an error in getenv\n");
            return ;
		}
	}
    else if (strcmp(arg[0], "-") == 0)
    {
        if (prev_dir[0] == '\0')
        {
            printf("minishell: cd: OLDPWD not set\n");
            return;
        }
        last = prev_dir;
        printf("%s\n", last);
    }
    else
        last = arg[0];
    if (chdir(last) != 0)
    {
        perror("cd failed");
        return;
    }
    strncpy(prev_dir, curr_dir, PATH_MAX);
}

void check_cmd(char *cmd, char **arg)
 {
	if (strcmp(cmd, "exit") == 0)
		{
			printf(RED"exitting shell ...\n"RESET);
			exit(0);
		}
	else if (strcmp(cmd, "echo") == 0)
	{
		ft_cmd_echo(arg);
		return ;
	}
	else if (strcmp(cmd, "cd") == 0)
	{
		ft_cmd_cd(arg);
		return ;
	}
	else
	{
		// execute_external(cmd, arg);
		printf("error\n");
		return ;
	}

 }

int main(int ac, char **av)
{
	char *read_input;
	char **valid_input;

	while (1)
	{
		read_input = readline(GREEN "minishell->$ " RESET);
		if (!read_input)
		{
			printf("exit\n");
			return (0);
		}
		add_history(read_input);
		valid_input = ft_split(read_input, ' ');
		if (valid_input && valid_input[0])
			check_cmd(valid_input[0], &valid_input[1]);
	}
}
