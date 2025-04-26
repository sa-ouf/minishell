#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <pwd.h>



void ft_cmd_cd(char **args) {
    char current_dir[PATH_MAX];
    static char previous_dir[PATH_MAX] = "";
    const char *target_dir = NULL;
    
    // Get current directory before changing
    if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
        perror("minishell: cd");
        return;
    }
    
    // Handle different cases
    if (args == NULL || args[0] == NULL || strcmp(args[0], "~") == 0) {
        // Case 1: cd with no arguments or "~" - go to home
        target_dir = getenv("HOME");
        if (target_dir == NULL) {
            struct passwd *pw = getpwuid(getuid());
            if (pw) target_dir = pw->pw_dir;
        }
        if (target_dir == NULL) {
            fprintf(stderr, "minishell: cd: HOME not set\n");
            return;
        }
    } else if (strcmp(args[0], "-") == 0) {
        // Case 2: cd - - go to previous directory
        if (previous_dir[0] == '\0') {
            fprintf(stderr, "minishell: cd: OLDPWD not set\n");
            return;
        }
        target_dir = previous_dir;
        printf("%s\n", target_dir);  // Print directory when using cd -
    } else {
        // Case 3: cd with path argument
        target_dir = args[0];
    }
    
    // Try to change directory
    if (chdir(target_dir) != 0) {
        perror("minishell: cd");
        return;
    }
    
    // Update previous directory if cd was successful
    strncpy(previous_dir, current_dir, PATH_MAX);
}

void check_cmd(char *cmd, char **arg) {
    if (strcmp(cmd, "exit") == 0) {
        printf(RED"exitting shell ...\n"RESET);
        exit(0);
    }
    // else if (strcmp(cmd, "echo") == 0) {
    //     ft_cmd_echo(arg);
    // }
    else if (strcmp(cmd, "cd") == 0) {
        ft_cmd_cd(arg);
    }
    else {
        // Instead of just printing "error", let's be more specific
        fprintf(stderr, "minishell: %s: command not found\n", cmd);
    }
    // No need for return statements since all paths either exit or return void
}

int main(int ac, char **av) {
    char *read_input;
    char **valid_input;

    while (1) {
        read_input = readline(GREEN "minishell->$ " RESET);
        if (!read_input) {
            printf("exit\n");
            return 0;
        }
        
        if (strlen(read_input) > 0) {
            add_history(read_input);
            valid_input = ft_split(read_input, ' ');
            if (valid_input && valid_input[0]) {
                check_cmd(valid_input[0], &valid_input[1]);
            }
            free(read_input);
        } else {
            free(read_input);
        }
    }
    return 0;
}


// int main(int ac, char **av)
// {
//     int i = 0;
//     int j;

//     while (av[i])
//     {
//         j = 0;
//         while (av[i][j])
//         {
//             if ((av[i][j] == '\'' || av[i][strlen(av[i]) - 1] == '\"') && (av[i][j] == '\'' || av[i][strlen(av[i]) - 1] == '\"')))
//         }
//     }
// }


// void remove_nl(char *str)
// {
// 	while (*str)
// 	{
// 		if (*str == '\n')
// 			*str = '\0';
// 		str++;
// 	}
// }
 // void ft_cmd_echo(char **arg)
// {
// 		int i = 0;
// 		int new_line = 1;

// 		while (arg[i] && arg[i][0] == '-' && arg[i][1] == 'n' && all_n(arg[i] + 1))
// 		{
// 			new_line = 0;
// 			i++;
// 		}
// 		while (arg[i])
// 		{
// 			remove_nl(arg[i]);
// 			int j = 0;
// 			printf("%c", arg[i][j]);
// 			if (arg[i][j] == 39 || arg[i][j] == 34)
// 				j++;
// 			printf(CYAN "%s"RESET, arg[i]);
// 			if (arg[i + 1])
// 			{
// 				printf(" ");
// 			}
// 			i++;
// 		}
// 		if (new_line)
// 			printf("\n");
// }
