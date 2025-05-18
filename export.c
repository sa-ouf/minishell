void add_new_var(char **arg, char **cpyenv)
{
	int i = 2;

	(void)cpyenv;
	// printf("%s\n", arg[i]);
}

void ft_cmd_export(char **arg, t_env *shell)
{
	int i = 0;
	int j = 0;
	int x = 0;
	char **cpyenv;

	while (shell->env[j])
		j++;
	while (arg[i])
	{
		if (strchr(arg[i], '='))
		{
			int l = 0;
			while (l < j)
			{
				if (strstr(shell->env[l], arg[i]))
					return ;
				l++;
			}
			cpyenv = malloc((j + 2) * sizeof(char *));
			if (!shell->env)
				return ;
			while (x < j)
			{
				cpyenv[x] = strdup(shell->env[x]);
				x++;
			}
			cpyenv[x] = strdup(arg[i]);
			cpyenv[x + 1] = NULL;
			// printf("%s %d\n", arg[i], i);
			// if (i > 0)
			// {
			// 	add_new_var(arg, cpyenv);
			// }
			int k = 0;
			while (k < j)
			{
				free(shell->env[k]);
				k++;
			}
			free(shell->env);
			shell->env = cpyenv;
			j++;
		}
		else
			printf("%s\n", arg[i]);
		i++;
	}
	return ;
}
