/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:53:04 by jllarena          #+#    #+#             */
/*   Updated: 2024/06/07 10:03:42 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char *ft_strcat(char *dest, const char *src)
{
    size_t dest_len = ft_strlen(dest);
    size_t i = 0;
    
    while (src[i] != '\0')
    {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';

    return dest;
}

static char *ft_strcpy(char *dst, const char *src)
{
    size_t i = 0;
    
    while (src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';

    return dst;
}

static char	**ft_free(char **split)
{
	int	limit;

	limit = 0;
	while (split[limit] != 0)
	{
		free(split[limit]);
		split[limit] = NULL;
		limit++;
	}
	free(split);
	split = NULL;
	return (0);
}

char *find_in_path(const char *cmd)
{
    char *path = getenv("PATH");
    if (path == NULL)
        return NULL;
    
    char **directories = ft_split(path, ':');
    if (directories == NULL)
        return NULL;

    int index = 0;
    while (directories[index] != NULL)
    {
        int len = ft_strlen(directories[index]) + ft_strlen(cmd) + 2; 
        char *full_path = (char *)malloc(len * sizeof(char)); 
        if (full_path == NULL)
        {
            ft_free(directories);
            return NULL;
        }
        ft_strcpy(full_path, directories[index]); 
        ft_strcat(full_path, "/"); 
        ft_strcat(full_path, cmd); 
        if (access(full_path, X_OK) == 0)
        {
            free(directories);
            return full_path; 
        }
        free(full_path); 
        index++;
    }
    ft_free(directories);
    return NULL; 
}
/*hdf*/