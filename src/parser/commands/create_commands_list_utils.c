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
