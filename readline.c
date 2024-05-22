#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "inc/libft/01-Libft/libft.h"


/*
int main() 
{
    const char *line;
    int i = 0;
    char **split;
    char **result;
    int result_index = 0;
    int j = 0;

    line = readline("Ingresa una línea de texto: ");

    split = ft_split(line, ' ');

    while (split[j])
    {
        j++;
    }
    // j = inidice inicial de cada palabra

    result = malloc(sizeof(char) * (j + 1));
    while (i < j)
    {
        if (split[i][0] == '-' && i > 0)
        {
            int len = ft_strlen(result[result_index - 1]) + ft_strlen(split[i]) + 2; //longitud de la palabra anterior y de la axtual 
            char *combined;
            combined = malloc(len * sizeof(char));
            strcpy(combined, result[result_index - 1]);
            strcat(combined, " ");
            strcat(combined, split[i]);
            result[result_index - 1] = combined;
        }
        else
        {
            result[result_index] = ft_strdup(split[i]);
            result_index++;
        }
        i++;
    }
    // Añadir el NULL al final del array result
    result[result_index] = NULL;
    i = 0;
    while (result[i])
    {
        printf("el resultado es: %s\n", result[i]);
        i++;
    }
    return 0;
}
*/
