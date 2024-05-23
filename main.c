/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:39:07 by jllarena          #+#    #+#             */
/*   Updated: 2024/05/23 19:01:33 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*int main(int argc, char **argv, char **envp)
{
    
}*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "inc/libft/01-Libft/libft.h"


int main() 
{
    const char *line;
    int i = 0;
    char **split;
    char **result;
    char *combined;
    int result_index = 0;
    int space_flag = 0;
    //int k = 0;
    //int l = 0;

    line = readline("Ingresa una línea de texto: ");

    split = ft_split(line, ' ');
    
    int f = 0;
    int j = 0;
    int quote = 0;

    /*while(split[j])
    {
    while(split[j][f])
    {   
    if(split[j][f] == 38)
    {
     write(1, &split[j][f], 1);
        printf("\n\n%d\n\n", quote);
        quote++;
        f++;
        while(split[j][f])
        {
            if(split[j][f] == 38 )
            {
                quote--;
                break ;
            }
            f++;
        }write(1, &split[j][f], 1);
    }write(1, &split[j][f], 1);
    if(split[j][f] == 34)
    {
        printf("P\n\n");
        f++;
        quote++;
        while(split[j][f])
        {
            if(split[j][f] == 34)
            {
                quote--;
                break ;
            }
            f++;
        }
    }
    f++;
    }
    j++;
    }
    printf("es: %d\n", quote);*/
    
    
    while (split[j])
        j++; // j = inidice inicial de cada palabra
    
 
    result = malloc(sizeof(char *) * (j + 1));

    while (i < j) 
    {
        if (split[i][0] == '-' && i > 0) {
            int len = ft_strlen(result[result_index - 1]) + ft_strlen(split[i]) + 2; // Longitud de la palabra anterior y de la actual
            combined = malloc(len * sizeof(char));
            ft_strlcpy(combined, result[result_index - 1], len);
            ft_strlcat(combined, " ", len);
            ft_strlcat(combined, split[i], len);
            result[result_index - 1] = combined;
        } 
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
            {
                space_flag = 1; // hay espacio
            }
        }
        i++;
    }

    result[result_index] = NULL;

    i = 0;
    while (result[i]) 
    {
        printf("El resultado es: %s\n", result[i]);
        i++;
    }
}

