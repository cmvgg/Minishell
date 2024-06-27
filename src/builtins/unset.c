/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:39:05 by cvarela-          #+#    #+#             */
/*   Updated: 2024/06/26 11:04:08 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_env(t_tokens *token, t_env *env)
{
	t_env	*prev;
	t_env	*curr;
	size_t	var_len;

	var_len = ft_strlen(token->str);
	prev = NULL;
	curr = env;
	while (curr && token->str)
	{
		if (!ft_strncmp(token->str, curr->str, var_len))
		{
			if (!prev)
				env = curr->next;
			else
				prev->next = curr->next;
			if (curr->was_added)
				free(curr->str);
			free(curr);
			break ;
		}
		prev = curr;
		curr = prev->next;
	}
}

int	unset(t_tokens *token, t_env *env)
{
	t_env	*head;

	head = env;
	if (!token->next || token->next->str == NULL || !token->next->str[0])
		return (printf("not enough arguments\n"));
	token = token->next;
	while (token)
	{
		env = head;
		unset_env(token, env);
		token = token->next;
	}
	env = head;
	return (1);
}
