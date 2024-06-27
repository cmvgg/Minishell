/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:54:40 by cvarela-          #+#    #+#             */
/*   Updated: 2024/06/24 19:55:23 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent(int fd_in, int count_pipes)
{
	int	i;

	i = 0;
	close(fd_in);
	while (i < count_pipes)
	{
		wait(NULL);
		i++;
	}
	close(fd_in);
}

void	close_write_read(int *pipes)
{
	close(pipes[0]);
	close(pipes[1]);
}

void	children(t_commands *commands, int fd_in, int count_pipes)
{
	int		i;
	int		pipes[2];
	pid_t	pid;

	i = 0;
	while (i < count_pipes)
	{
		pipe(pipes);
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
				dup2(fd_in, STDIN_FILENO);
			if ((i + 1) != count_pipes)
				dup2(pipes[1], STDOUT_FILENO);
			close_write_read(pipes);
			parser(commands);
			exit(g_exit_status);
		}
		dup2(pipes[0], fd_in);
		close_write_read(pipes);
		commands = commands->next;
		i++;
	}
	free(commands);
}

void	open_pipe(t_commands *commands)
{
	int		fd_in;
	int		count_pipes;

	count_pipes = lstsize_commands(commands);
	if (count_pipes > 1)
	{
		fd_in = dup(STDIN_FILENO);
		children(commands, fd_in, count_pipes);
		parent(fd_in, count_pipes);
	}
	else
		parser(commands);
}
