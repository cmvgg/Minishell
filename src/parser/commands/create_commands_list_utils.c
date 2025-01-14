/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_list_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:39:43 by cvarela-          #+#    #+#             */
/*   Updated: 2024/06/26 19:37:47 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute(t_commands *command, int flag)
{
	while (command)
	{
		if (flag == 1)
			check_heredoc(command->token);
		else
			files_exist(command->token);
		command = command->next;
	}
}

void	remake_commands(t_commands *commands)
{
	t_commands	*head;

	head = commands;
	execute(head, 1);
	execute(head, 2);
}
