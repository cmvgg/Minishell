/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bins_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:36:12 by cvarela-          #+#    #+#             */
/*   Updated: 2024/06/24 19:36:52 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(t_env *env)
{
	char	**path;
	char	*value;

	value = env_value("PATH", env);
	if (value)
	{
		path = ft_splitmeta(value, ':');
		free(value);
		return (path);
	}
	free(value);
	return (NULL);
}

char	*get_bin_path(char *path, char *str)
{
	char	*bin_path;
	char	*small_bin_path;

	small_bin_path = ft_strjoin(path, "/");
	bin_path = ft_strjoin(small_bin_path, str);
	free(small_bin_path);
	free(path);
	return (bin_path);
}

void	check_heredoc(t_tokens *token)
{
	int			fd;

	fd = 0;
	while (token)
	{
		if (!token->skip && token->type == HEREDOC && token->next)
		{
			heredoc_while(token->next->str);
			fd = open("/tmp/1", O_RDONLY, 0644);
			dup2(fd, STDIN_FILENO);
			unlink("/tmp/1");
			token->skip = 1;
		}
		token = token->next;
	}
}

void	execute_cicle(char *delim_line)
{
	int		fd;
	int		output;
	char	buff[4095];

	handle_signal_redir();
	write(1, "> ", 2);
	fd = open("/tmp/1", O_RDWR | O_CREAT | O_TRUNC, 0644);
	output = read(1, buff, 4095);
	while (output > 0)
	{
		handle_signal_redir();
		buff[output] = '\0';
		if (!ft_strcmp(buff, delim_line))
			break ;
		ft_putstr_fd(buff, fd);
		write(1, "> ", 2);
		output = read(1, buff, 4095);
	}
	close (fd);
}
