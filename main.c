

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "inc/libft/01-Libft/libft.h"
#include "minishell.h"

void ft_quote(char **result)
{
    int j = 0;
    int quote = 0;
	int simple;

	simple = 0;
    while(result[j])
    {
        int f = 0; 
        while(result[j][f])
        {
            if((result[j][0] == 34) || ((result[j][f] == 39) && simple++)) 
            {
                quote++;
                f++;
                while(result[j][f])
                {
                    if((result[j][f] == 34) || ((result[j][f] == 39) && (simple != 0)))
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
    if(quote != 1)
	perror("syntax error");
}


char *combined(char *prev_word, char *current_word)
{
    int len = ft_strlen(prev_word) + ft_strlen(current_word) + 2;
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
        j++; 
    
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
				space_flag = 1;
        }
        i++;
    }

    result[result_index] = NULL;
    return result;
}

void ft_free(char **result)
{
	int i;

	i = 0;
	while (result[i])
    {
		free(result[i]);
        i++;
    }
}

int main(void)
{
    const char *line;
	char **split;
	char **result;

	split = NULL;
	result = NULL;
    line = readline("Ingresa una línea de texto: ");
    split = ft_splitmeta(line, ' ');
    if(!split)
        return 0;
	else
	{
	result = runspace(split);
	ft_quote(result);
	ft_free(result);
	if(result)
		free(result);
	free(split);
	return (0);
	}
}
