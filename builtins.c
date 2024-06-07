/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:16:31 by jllarena          #+#    #+#             */
/*   Updated: 2024/06/07 10:03:36 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdbool.h>
#include <string.h>
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include "inc/libft/01-Libft/libft.h"


char **split_by_pipes(const char *line)
{
    return ft_splitmeta(line, '|');
}

bool is_builtin(const char *cmd)
{
    int i = 0;
    
    const char *builtins[] = {"cd", "echo", "unset", "env", "export", "exit", "pwd", NULL};
    while (builtins[i] != NULL)
    {
        if (strcmp(cmd, builtins[i]) == 0)
            return true;
        i++;
    }
    return false;
}

bool is_executable_file(const char *cmd)
{
    if (access(cmd, X_OK) == 0)
        return (true);
    return (false);
}
/*akwlefnj */
/*drgs*/

int open_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
    }
    return fd;
}