/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:39:55 by cvarela-          #+#    #+#             */
/*   Updated: 2024/07/02 15:25:43 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*lstlast_commands(t_commands *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lstadd_back_commands(t_commands **lst, t_commands *new)
{
	t_commands	*tail;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tail = lstlast_commands(*lst);
	tail->next = new;
}

int	lstsize_commands(t_commands *commands)
{
	int	count;

	count = 0;
	while (commands)
	{
		count++;
		commands = commands->next;
	}
	return (count);
}

static void	process_command_list(t_commands *head)
{
	if (head == NULL)
		return ;
	remake_commands(head);
	open_pipe(head);
	free_structs2(head);
}

void	pipe_commands(char *str, t_env *env)
{
	t_commands	*head;
	char		**pipe_splitted;

	pipe_splitted = split_commands(str);
	if (pipe_splitted == NULL)
	{
		if (pipe_splitted[0])
			free_pipe_splitted(pipe_splitted);
		free(str);
		return ;
	}
	head = create_command_list(pipe_splitted[0], env);
	if (head == NULL)
	{
		free_pipe_splitted(pipe_splitted);
		free(str);
		return ;
	}
	add_nodes_to_command_list(&head, pipe_splitted, env);
	free_pipe_splitted(pipe_splitted);
	process_command_list(head);
}
