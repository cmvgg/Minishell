/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:58:08 by cvarela-          #+#    #+#             */
/*   Updated: 2024/07/02 15:23:26 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	g_exit_status = 0;

int	check_line(char *line)
{
	int		i;
	int		pos;

	i = -1;
	if (!line)
	{
		printf("exit\n");
		exit(g_exit_status);
	}
	pos = search_ops_in_str(line, "|");
	if (has_open_quotes(line, ft_strlen(line)))
	{
		g_exit_status = 2;
		add_history(line);
		printf("%s\n", EPROMPT);
		return (0);
	}
	if (pos != -1)
	{
		while (++i < pos)
			if (line[i] != ' ' && line[i] != '\t')
				return (1);
		return (printf("%s\n", EPARSE), 0);
	}
	return (1);
}

char	*check_dpipe(char *line)
{
	int		i;
	char	*new_line;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '|' && (line[i - 1] == '|' || line[i + 1] == '|'))
		{
			new_line = ft_substr(line, 0, i);
			add_history(line);
			free(line);
			return (new_line);
		}
	}
	add_history(line);
	return (ft_strtrim(line, " "));
}

void	all(char *line, t_env *env, int fd)
{
	while (1)
	{
		dup2(fd, STDIN_FILENO);
		line = readline(PROMPT);
		if (!check_line(line) || crazy(line))
			continue ;
		line = check_dpipe(line);
		if (ft_strlen(line))
			pipe_commands(line, env);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*env;
	int			fd;

	(void)argv;
	line = NULL;
	env = NULL;
	handle_global_signals();
	if (argc == 1)
	{
		fd = dup(STDIN_FILENO);
		env = init_env(envp);
		all(line, env, fd);
		close(fd);
	}
	else
		printf("Error: Too many arguments!\n");
	if (env)
		free_env(env);
	free(env);
	return (0);
}
