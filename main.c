/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:39:07 by jllarena          #+#    #+#             */
/*   Updated: 2024/05/22 19:26:51 by jllarena         ###   ########.fr       */
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
    int j = 0;
    int space_flag = 0; 

    line = readline("Ingresa una línea de texto: ");

    split = ft_split(line, ' ');

    while (split[j])
        j++; // j = inidice inicial de cada palabra
    
    result = malloc(sizeof(char *) * (j + 1));

    while (i < j) 
    {
        if (split[i][0] == '-' && i > 0) {
            int len = strlen(result[result_index - 1]) + strlen(split[i]) + 2; // Longitud de la palabra anterior y de la actual
            combined = malloc(len * sizeof(char));
            strcpy(combined, result[result_index - 1]);
            strcat(combined, " ");
            strcat(combined, split[i]);
            result[result_index - 1] = combined;
        } 
        else 
        {
            if (split[i][0] != '\0' && split[i][0] != ' ')
            {
                if (space_flag == 0)
                {
                    result[result_index] = strdup(split[i]);
                    result_index++;
                } 
                else 
                {
                    if (result_index != 0) 
                    {
                        result[result_index] = strdup(" ");
                        result_index++;
                    }
                    result[result_index] = strdup(split[i]);
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
