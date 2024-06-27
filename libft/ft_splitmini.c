/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitmini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:22:06 by jllarena          #+#    #+#             */
/*   Updated: 2024/06/27 19:42:20 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*size_t	wordcount(char **split, char const *s, char c, size_t limit,
				size_t	word_count)
{
	size_t	init;
	size_t	final;
	bool	in_quotes;
	char	quote_char;

	init = 0;
	final = 0;
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
		split[limit] = malloc(sizeof(char) * (final - init + 1));
		if (!split[limit])
			return (ft_free(split), 0);
		ft_strlcpyquote(split[limit], s + init, final - init + 1);
		limit++;
	}
	return (limit);
}

char	**ft_splitmeta(char const *s, char c)
{
	char	**split;
	size_t	limit;
	size_t	word_count;
	size_t	i;

	limit = 0;
	word_count = ft_count_word(s, c);
	i = 0;
	if (word_count == 0)
		return (NULL);
	split = malloc((word_count + 1) * sizeof(char *));
	if (!split)
		return (0);
	while (i <= word_count)
	{
		split[i] = NULL;
		i++;
	}
	limit = wordcount(split, s, c, limit, word_count);
	split[limit] = 0;
	return (split);
}*/

static size_t	skip_delimiters(const char *s, char c, size_t pos)
{
	while (s[pos] == c && s[pos] != 0)
		pos++;
	return (pos);
}

static t_word_pos	find_word_end(const char *s, char c, size_t start)
{
	t_word_pos	pos;

	pos.start = start;
	pos.end = start;
	pos.in_quotes = false;
	pos.quote_char = '\0';
	while (s[pos.end] != 0 && (s[pos.end] != c || pos.in_quotes))
	{
		if ((s[pos.end] == 34 || s[pos.end] == 39) && !pos.in_quotes)
		{
			pos.in_quotes = true;
			pos.quote_char = s[pos.end];
		}
		else if (s[pos.end] == pos.quote_char && pos.in_quotes)
			pos.in_quotes = false;
		pos.end++;
	}
	return (pos);
}

static bool	allocate_and_copy_word(t_split_params *params, t_word_pos pos,
	size_t idx)
{
	params->split[idx] = malloc(sizeof(char) * (pos.end - pos.start + 1));
	if (!params->split[idx])
		return (false);
	ft_strlcpyquote(params->split[idx], params->s + pos.start,
		pos.end - pos.start + 1);
	//free(params->split[idx]);
	return (true);
}

size_t	wordcount(t_split_params *params, size_t limit)
{
	t_word_pos	pos;

	pos.start = 0;
	pos.end = 0;
	pos.in_quotes = false;
	pos.quote_char = '\0';
	while (params->split[limit] == NULL)
	{
		pos.start = skip_delimiters(params->s, params->c, pos.end);
		pos = find_word_end(params->s, params->c, pos.start);
		if (pos.end == pos.start)
			break ;
		if (!allocate_and_copy_word(params, pos, limit))
			return (0);
		limit++;
	}
	return (limit);
}

char	**ft_splitmeta(const char *s, char c)
{
	char			**split;
	size_t			limit;
	size_t			word_count;
	t_split_params	params;
	size_t			i;

	limit = 0;
	i = -1;
	word_count = ft_count_word(s, c);
	if (word_count == 0)
		return (NULL);
	split = malloc((word_count + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (++i <= word_count)
		split[i] = NULL;
	params.split = split;
	params.s = s;
	params.c = c;
	limit = wordcount(&params, limit);
	if (!limit)
		return (ft_free(split), NULL);
	split[limit] = NULL;
	return (split);
}
