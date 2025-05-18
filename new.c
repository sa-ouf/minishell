/*#include "minishell.h"
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
	const char *pur;
	
	if (arg[0] == NULL)
	{
		return;
	}
	else if (arg[1] != NULL)
	{
		printf("minishell: cd: too many arguments\n");
		return;
	}
	else
		pur = arg[0];
	if (chdir(pur) != 0)
		printf("minishell: cd: %s: \n", pur);
}

void ft_cmd_env(t_shell *shell)
{
    int i = 0;
    while (shell->env[i])
    {
        printf("%s\n", shell->env[i]);
        i++;
    }
}


// void ft_cmd_env(char *cmd, char **arg, t_shell *my_shell)
// {
// 	if (arg[0] && cmd != NULL)
// 	{
// 		// printf("%s", cmd);
// 		// printf("\n%s\n", arg[0]);
// 		int i = 0;
// 		while (my_shell->env[i])
// 		{
// 			if (strstr(my_shell->env[i], arg[0]) != NULL)
// 			{
// 				printf("%s\n", my_shell->env[i]);
// 			}
// 			i++;
// 		}
// 	}
// 	else
// 	{
// 		int i = 0;
// 		while (my_shell->env[i])
// 		{
// 			printf("%s\n", my_shell->env[i]);
// 			i++;
// 		}
// 	}
// }

char **realloc_env(char **env, int new_size)
{
    char **new_env = malloc(sizeof(char *) * new_size);
    int i = 0;
    while (env && env[i])
    {
        new_env[i] = env[i];
        i++;
    }
    new_env[i] = NULL;
    free(env);
    return new_env;
}

void add_or_update_env(t_shell *shell, char *new_var)
{
    int i = 0;
    char *key = strdup(new_var);
    char *equal_sign = strchr(key, '=');
    if (equal_sign)
        *equal_sign = '\0'; // split key=value into key

    while (shell->env[i])
    {
        if (strncmp(shell->env[i], key, strlen(key)) == 0 && shell->env[i][strlen(key)] == '=')
        {
            free(shell->env[i]);
            shell->env[i] = strdup(new_var);
            free(key);
            return;
        }
        i++;
    }

    // Add new variable
    shell->env = realloc_env(shell->env, i + 2);
    shell->env[i] = strdup(new_var);
    shell->env[i+1] = NULL;
    free(key);
}


void export_cmd(char **arg, t_shell *shell)
{
    int i = 0;
    while (arg[i])
    {
        if (strchr(arg[i], '='))
		{
			int x = 0;
            add_or_update_env(shell, arg[i]);
			while (shell->env[x])
			{
				printf("%s\n", shell->env[x]);
				x++;
			}
		}
        else
            printf("export: `%s`: not a valid identifier\n", arg[i]);
        i++;
    }
}

// void export_cmd(char **arg, t_shell *shell)
// {
// 	// char *store_v;
// 	int i = 0;

// 	int j = 0;
// 	shell->env[j] = malloc(i + 1);
// 	if (!shell->env[j])
// 		return ;
// 	strcat(shell->env[j], arg[0]);
// 	int x = 0;
// 	while (shell->env[x])
// 	{
// 		printf("%s\n", shell->env[x]);
// 		x++;
// 	}
	
// }
// j++;
	// }
	// shell->env = malloc(i + 1);
	// if (!shell->env)
	// 	return ;
	// int x = 0;
	// while (arg[0])
	// {
	// 	shell->env[j][x] = arg[0];
		// x++;
		// j++;
// store_v[j] = arg[0][i];
// store_v[j] = '\0';


void execute_cmd(char *cmd, char **args) 
{
    int pid;
	int status;

	pid = fork();
    if (pid == -1) 
	{
        perror("fork"); 
        exit(1);
    } 
    else if (pid == 0)
	{ 
        execvp(cmd, args);
        exit(1);
    } 
    else 
        waitpid(pid, &status, 0);
}

void check_cmd(char *cmd, char **arg, t_shell *my_shell)
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
	else if (strcmp(cmd, "export") == 0)
	{
		// if (strcmp(cmd, "env") == 0 && arg[0] )
		export_cmd(arg, my_shell);
		return ;
	}
	else if (strcmp(cmd, "env") == 0)
	{
				ft_cmd_env(my_shell);
				return ;
	}
	else
	{
		// execute_cmd(cmd, arg);
		return ;
	}

 }

 char **copy_env(char **envp)
{
    int i = 0;
    char **new_env;

    while (envp[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (envp[i])
    {
        new_env[i] = strdup(envp[i]);
        i++;
    }
    new_env[i] = NULL;
    return new_env;
}

// char **copy_env(char **str)
// {
// 	char **my_env;
// 	int i = 0;

// 	while (str[i])
// 		i++;
// 	my_env = malloc((i + 1) * sizeof(char *));
// 	if (!my_env)
// 		return (NULL);
// 	i = 0;
// 	while (str[i])
// 	{
// 		my_env[i] = strdup(str[i]);
// 		i++;
// 	}
// 	my_env[i] = NULL;
// 	return (my_env);
// }

int main(int ac, char **av, char **envp)
{
	t_shell my_shell;
	char *read_input;
	char **valid_input;

	(void)av;
	my_shell.env = copy_env(envp);  // ← Copy once at the start!

	while (1)
	{
		read_input = readline(GREEN "my_shell->$ " RESET);
		if (!read_input)
		{
			printf("exit\n");
			return (0);
		}
		add_history(read_input);
		valid_input = ft_split(read_input, ' ');
		if (valid_input && valid_input[0])
			check_cmd(valid_input[0], &valid_input[1], &my_shell);
	}
}*/
