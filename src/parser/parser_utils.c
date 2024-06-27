/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:41:03 by cvarela-          #+#    #+#             */
/*   Updated: 2024/06/24 19:41:05 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_content(char *str, char *op, int flag)
{
	char	*string;
	int		size;

	if (!flag)
	{
		if (str[0] != op[0])
			return (1);
		return (0);
	}
	else
	{
		string = ft_strchr(str, op[0]);
		size = ft_strlen(op);
		if (string[size] && string[size] != op[0])
			return (1);
		return (0);
	}
}

void	handle_content_before(t_tokens *token, int pos,
	char *op, char *original_str)
{
	char		*str;
	t_tokens	*op_token;

	str = token->str;
	token->str = ft_substr(str, 0, pos);
	free(str);
	token->type = token_type(token->str, 0, token->was_quoted);
	op_token = lstnew_token(ft_strdup(op), token_type(op, 0, 0));
	if (!search_content(original_str, op, 1))
		op_token->next = token->next;
	token->next = op_token;
}

t_tokens	*handle_content_after(char *original_str, int pos,
	char *op, t_tokens *token)
{
	int			quant;
	char		*new_str;
	t_tokens	*new_token;

	if (ft_strlen(original_str) != ft_strlen(token->str))
		quant = ft_strlen(original_str) - ft_strlen(op)
			- ft_strlen(token->str);
	else
		quant = ft_strlen(original_str) - ft_strlen(op);
	new_str = ft_substr(original_str, pos + ft_strlen(op), quant);
	new_token = lstnew_token(new_str, token_type(new_str, 0, 0));
	if (!search_content(original_str, op, 0))
	{
		free(token->str);
		token->str = ft_strdup(op);
		token->type = token_type(op, 0, 0);
		token->next = new_token;
	}
	else
		token->next->next = new_token;
	return (new_token);
}

char	*quote_handler(char *str, int *pos, int start, t_env *env)
{
	char	*new_str;

	(*pos)++;
	new_str = NULL;
	if (str[(*pos) - 1] == PLICAS)
	{
		while (str[*pos] && str[*pos] != PLICAS)
			(*pos)++;
		new_str = add_chars(new_str, str, ((*pos) - start), start);
		return (new_str);
	}
	while (str[*pos] && str[*pos] != ASPAS)
	{
		while (str[*pos] != '$' && str[*pos] && str[*pos] != ASPAS)
			(*pos)++;
		if (str[(*pos) - 1] != ASPAS)
			new_str = add_chars(new_str, str, ((*pos) - start), start);
		if (str[*pos] == '$')
		{
			new_str = process_variable(str, pos, new_str, env);
			start = *pos;
		}
	}
	return (new_str);
}

char	*process_variable(char *str, int *i, char *expanding, t_env *env)
{
	char	*new_str;
	char	*temp;

	temp = search_variable(str, i, env);
	if (expanding)
	{
		if (temp)
			new_str = ft_strjoin(expanding, temp);
		else
			new_str = ft_strdup(expanding);
		if (ft_strcmp(expanding, "$"))
			free(expanding);
		if (temp && ft_strcmp(temp, "$"))
			free(temp);
		return (new_str);
	}
	return (temp);
}
