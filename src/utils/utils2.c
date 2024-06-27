/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:56:45 by cvarela-          #+#    #+#             */
/*   Updated: 2024/06/26 15:22:19 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_ops(void)
{
	char	**ops;

	ops = (char **)malloc(sizeof(char *) * 5);
	ops[0] = ">";
	ops[1] = "<";
	ops[2] = ">>";
	ops[3] = "<<";
	ops[4] = 0;
	return (ops);
}

char	**fill_env_matrix(t_env *env)
{
	int		i;
	int		size;
	char	**envp;
	t_env	*node;

	node = env;
	size = env_len(node);
	envp = (char **)malloc(sizeof(char *) * (size + 1));
	envp[size] = 0;
	i = -1;
	while (++i < size)
	{
		envp[i] = ft_strdup(node->str);
		if (node->next)
			node = node->next;
	}
	return (envp);
}

char	**fill_args(t_tokens *token)
{
	int			i;
	int			size;
	char		**args;
	t_tokens	previous;

	previous = *token;
	size = lstsize_tokens(token, 1);
	args = (char **)malloc(sizeof(char *) * (size + 1));
	args[size] = 0;
	i = 0;
	while (i < size)
	{
		if (!is_redirect(token->str,
				token->was_quoted) && !is_redirect(previous.str,
				previous.was_quoted))
		{
			args[i] = ft_strdup(token->str);
			i++;
		}
		previous = *token;
		token = token->next;
	}
	return (args);
}

int	is_accepted(t_tokens *token)
{
	if (!ft_strcmp(token->str, "$?"))
	{
		if (token->type == COMMAND)
			return (0);
	}
	return (1);
}

int	is_bin(char *str)
{
	int		res;
	char	*temp;

	if (str[0] == '.' && str[1] == '/' && str[2] != '\0')
		return (1);
	res = 0;
	temp = ft_substr(str, 1, 3);
	if (!ft_strcmp(temp, "bin"))
		res = 1;
	free(temp);
	return (res);
}
