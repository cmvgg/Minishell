#include "minishell.h"

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

static t_commands	*lstlast_commands(t_commands *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	lstadd_back_commands(t_commands **lst, t_commands *new)
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

void	pipe_commands(char *str, t_env *env)
{
	int			i;
	char		**pipe_splitted;
	t_commands	*head;
	t_commands	*current_node;

	i = 0;
	pipe_splitted = ft_split(str, '|');
	if (has_empty_pipe(pipe_splitted))
	{
		g_exit_status = 1;
		printf("%s\n", EPARSE);
		return ;
	}
	head = lstnew_commands(token_list(pipe_splitted[i]), env);
	current_node = head;
	while (pipe_splitted[++i])
	{
		current_node = lstnew_commands(token_list(pipe_splitted[i]), env);
		lstadd_back_commands(&head, current_node);
	}
	free(pipe_splitted);
	remake_commands(head);
	open_pipe(head);
	free_structs(head, 0);
}