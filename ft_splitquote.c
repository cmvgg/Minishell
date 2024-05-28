/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:37:52 by jllarena          #+#    #+#             */
/*   Updated: 2024/05/28 16:51:45 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "inc/libft/01-Libft/libft.h"

static void	ft_strlcpyquote(char *dst, const char *src, size_t size) 
{
	size_t i = 0;

	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static size_t	ft_count_word(char const *s, char c)
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

static char	**ft_free(char **split)
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

char	**ft_splitquote(char const *s, char c)
{
	char	**split;
	size_t	limit = 0;
	size_t	init = 0;
	size_t	final = 0;
	bool in_quotes = false;
	char quote_char = '\0';

	split = malloc((ft_count_word(s, c) + 1) * sizeof(char *));
	if (!split)
		return 0;

	while (limit < ft_count_word(s, c))
	{
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
		split[limit] = malloc(sizeof(char) * (final - init + 1));
		if (!split[limit])
			return (ft_free(split));
		ft_strlcpyquote(split[limit], s + init, final - init + 1);
		limit++;
	}
	split[limit] = 0;
	return split;
}

/*int main()
{
	char **result;
	char *str = "This is a 'test string' with \"quoted parts\" included";
	char delimiter = ' ';

	result = ft_splitquote(str, delimiter);
	if (result)
	{
		int i = 0;
		while (result[i]) 
		{
			printf("%s\n", result[i]);
			free(result[i]);
			i++;
		}
		free(result);
	}
	return 0;
}*/
