/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_list_utils2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:37:34 by jllarena          #+#    #+#             */
/*   Updated: 2024/07/02 15:28:17 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_commands	*lstnew_commands(t_tokens *token, t_env *env)
{
	t_commands	*node;

	node = malloc(sizeof(t_commands));
	if (node == NULL)
		return (NULL);
	node->token = token;
	node->env = env;
	node->next = NULL;
	return (node);
}

char	**split_commands(char *str)
{
	char	**pipe_splitted;

	pipe_splitted = ft_splitmeta(str, '|');
	if (pipe_splitted == NULL)
		return (NULL);
	if (has_empty_pipe(pipe_splitted))
	{
		g_exit_status = 1;
		printf("%s\n", EPARSE);
		free(pipe_splitted);
		return (NULL);
	}
	return (pipe_splitted);
}

t_commands	*create_command_list(char *str, t_env *env)
{
	t_commands	*head;

	head = lstnew_commands(token_list(str), env);
	if (head == NULL)
		return (NULL);
	head->next = NULL;
	return (head);
}

void	free_pipe_splitted(char **pipe_splitted)
{
	free(pipe_splitted);
}

void	add_nodes_to_command_list(t_commands **head, char **pipe_splitted,
				t_env *env)
{
	int			i;
	t_commands	*node;

	i = 1;
	while (pipe_splitted[i])
	{
		node = lstnew_commands(token_list(pipe_splitted[i]), env);
		if (node == NULL)
		{
			free_structs2(*head);
			*head = NULL;
			return ;
		}
		lstadd_back_commands(head, node);
		i++;
	}	
}
