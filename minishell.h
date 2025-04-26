
#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define GREEN   "\033[0;32m"
#define CYAN  "\033[0;36m"
#define RED   "\033[0;31m"
#define RESET "\033[0m"

char    **ft_split(char const *s, char c);

#endif
