/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:39:07 by jllarena          #+#    #+#             */
/*   Updated: 2024/05/28 17:18:22 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "inc/libft/01-Libft/libft.h"
#include "minishell.h"

int ft_quote(char **result)
{
    int j = 0;
    int quote = 0;

    while(result[j])
    {
        int f = 0; 
        while(result[j][f])
        {   
            if(result[j][f] == 39) 
            {
                quote++;
                f++;
                while(result[j][f])
                {
                    if(result[j][f] == 39 )
                    {
                        quote--;
                        f++; 
                        break;
                    }
                    f++;
                }
            }
            else if(result[j][f] == 34) 
            {   
                quote++;
                f++;
                while(result[j][f])
                {
                    if(result[j][f] == 34)
                    {
                        quote--;
                        f++; 
                        break;
                    }
                    f++;
                }
            }
            f++;
        }
        j++;
    }
    return (quote);
}


char *combined(char *prev_word, char *current_word)
{
    int len = ft_strlen(prev_word) + ft_strlen(current_word) + 2; // Longitud de la palabra anterior y de la actual
    char *combined = malloc(len * sizeof(char));
    ft_strlcpy(combined, prev_word, len);
    ft_strlcat(combined, " ", len);
    ft_strlcat(combined, current_word, len);
    return combined;
}


char **runspace(char **split)
{
    int i = 0;
    int result_index = 0;
    int space_flag = 0;
    int j = 0;
    
    while (split[j])
        j++; // j = índice inicial de cada palabra
    
    char **result = malloc(sizeof(char *) * (j + 1));

    while (i < j)
    {
        if (split[i][0] == '-' && i > 0)
        	result[result_index - 1] = combined(result[result_index - 1], split[i]);
        else
		{
            if (split[i][0] != '\0' && split[i][0] != ' ')
			{
                if (space_flag == 0)
				{
                    result[result_index] = ft_strdup(split[i]);
                    result_index++;
                } 
                else
				{
                    result[result_index] = ft_strdup(split[i]);
                    result_index++;
                    space_flag = 0;
                }
            }
            else
            	space_flag = 1; // hay espacio
        }
        i++;
    }

    result[result_index] = NULL;
    return result;
}



int main()
{
    const char *line;
    
    line = readline("Ingresa una línea de texto: ");

    char **split = ft_splitmeta(line, ' ');
    char **result = runspace(split);
	int quote = ft_quote(result);
    int i = 0;
    
    
    while (result[i])
    {
        printf("El resultado es: %s\n", result[i]);
        i++;
    }
    
	printf("quote es %d\n", quote);
    i = 0;
    while (result[i])
	{
        free(result[i]);
        i++;
    }
    free(result);

    return 0;
}

/*
int main()
{
    int i = 0;
    char *str[] = {"wñigf suiahfi "awef" 'aoihfoh", NULL};
    
    while(str[i])
	{
        printf("%d\n", ft_quote(str));
        i++;
    }
    
    return 0;
}*/


