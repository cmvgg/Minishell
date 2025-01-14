/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:06:53 by cvarela-          #+#    #+#             */
/*   Updated: 2024/06/24 17:37:07 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_advance_quotes(const char *s, size_t *index, char delimiter)
{
	bool	in_quotes;
	char	quote_char;

	in_quotes = false;
	quote_char = '\0';
	while (s[*index] != 0 && (s[*index] != delimiter || in_quotes))
	{
		if ((s[*index] == 34 || s[*index] == 39) && !in_quotes)
		{
			in_quotes = true;
			quote_char = s[*index];
		}
		else if (s[*index] == quote_char && in_quotes)
			in_quotes = false;
		(*index)++;
	}
	return (in_quotes);
}

size_t	ft_count_word(char const *s, char c)
{
	size_t	init;
	size_t	count;

	init = 0;
	count = 0;
	while (s[init] != 0)
	{
		while (s[init] == c && s[init] != 0)
			init++;
		if (s[init] != 0)
		{
			count++;
			ft_advance_quotes(s, &init, c);
		}
	}
	return (count);
}
