/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitmeta.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:48:55 by jllarena          #+#    #+#             */
/*   Updated: 2024/06/07 10:03:47 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minishell.h"
#include "inc/libft/01-Libft/libft.h"

static int is_space(char c)
{
    if ((c >= 9 && c <= 13) || c == 32)
        return 1;
    return 0;
}

static void ft_strlcpyquote(char *dst, const char *src, size_t size)
{
    size_t i = 0;

    while (i < size - 1 && src[i])
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

static size_t ft_count_word(char const *s, char c)
{
    size_t init = 0;
    size_t count = 0;
    bool in_quotes = false;
    char quote_char = '\0';

    while (s[init] != 0)
    {
        while (s[init] == c && s[init] != 0)
            init++;
        if (s[init] != 0)
        {
            count++;
            while (s[init] != 0 && (s[init] != c || in_quotes))
            {
                if ((s[init] == 34 || s[init] == 39) && !in_quotes)
                {
                    in_quotes = true;
                    quote_char = s[init];
                }
                else if (s[init] == quote_char && in_quotes)
                    in_quotes = false;
                init++;
            }
        }
    }
    return count;
}

static char **ft_free(char **split)
{
    int limit = 0;

    while (split[limit] != 0)
    {
        free(split[limit]);
        split[limit] = NULL;
        limit++;
    }
    free(split);
    split = NULL;
    return 0;
}

static int check_syntax(const char *s, size_t init, size_t final)
{
    size_t i = init;

    while (i < final)
    {
        if (s[i] == '|')
        {
            if ((i > 0 && !is_space(s[i - 1])) || (i + 1 < final && !is_space(s[i + 1])))
            {
                printf("syntax error\n");
                return (-1);
            }
        }
        else if (s[i] == '>' || s[i] == '<')
        {
            if ((s[i] == '>' && i + 1 < final && s[i + 1] == '>') || 
                (s[i] == '<' && i + 1 < final && s[i + 1] == '<'))
            {
                if ((i > 0 && !is_space(s[i - 1])) || (i + 2 < final && !is_space(s[i + 2])))
                {
                    printf("syntax error\n");
                    return (-1);
                }
                i++;
            }
            else
            {
                if ((i > 0 && !is_space(s[i - 1])) || (i + 1 < final && !is_space(s[i + 1])))
                {
                    printf("syntax error\n");
                    return (-1);
                }
            }
        }
        i++;
    }
    return (0);
}

char **ft_splitmeta(char const *s, char c)
{
    char **split;
    size_t limit = 0;
    size_t init = 0;
    size_t final = 0;
    bool in_quotes;
    char quote_char;

    size_t word_count = ft_count_word(s, c);
    if (word_count == 0)
        return NULL;

    split = malloc((word_count + 1) * sizeof(char *));
    if (!split)
        return 0;

    size_t i = 0;
    while (i <= word_count)
    {
        split[i] = NULL;
        i++;
    }

    while (limit < word_count)
    {
        in_quotes = false;
        quote_char = '\0';

        init = final;
        while (s[init] == c && s[init] != 0)
            init++;
        final = init;
        while (s[final] != 0 && (s[final] != c || in_quotes))
        {
            if ((s[final] == 34 || s[final] == 39) && !in_quotes)
            {
                in_quotes = true;
                quote_char = s[final];
            }
            else if (s[final] == quote_char && in_quotes)
                in_quotes = false;
            final++;
        }

        if (check_syntax(s, init, final) == -1)
        {
            ft_free(split);
            return NULL;
        }

        bool contains_dollar = false;
        if (quote_char == 34 && !in_quotes)
        {
            size_t i = init;
            while (i < final)
            {
                if (s[i] == '$')
                {
                    contains_dollar = true;
                    break;
                }
                i++;
            }
        }

        split[limit] = malloc(sizeof(char) * (final - init + 1));
        if (!split[limit])
        {
            ft_free(split);
            return NULL;
        }

        ft_strlcpyquote(split[limit], s + init, final - init + 1);

        if (contains_dollar)
        {
            // expand_variable();   LLAMADA A LA FUNCION PARA EXPANDIR
            ft_strlcat(split[limit], " (contain $)", 10);
        }

        limit++;
    }
    split[limit] = 0;
    return split;
}
/*dh*/

/*int main()
{
	char **result = ft_splitmeta("Testeo esto "$fwe" feb" , ' ');

	size_t i = 0;
	while (result[i] != NULL)
    {
		printf("%s\n", result[i]);
		free(result[i]);
		i++;
	}
	free(result);

	return 0;
}*/


