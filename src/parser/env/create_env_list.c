#include "minishell.h"

t_env	*lstnew_env(char *envp, int flag)
{
	t_env	*node = malloc(sizeof(t_env));
	if (node)
	{
		node->was_added = flag;
		node->str = envp;
		node->next = NULL;
	}
	return node;
}

static t_env	*lstlast_env(t_env *lst)
{
	if (!lst)
		return NULL;
	while (lst->next)
		lst = lst->next;
	return lst;
}

void	lstadd_back_env(t_env *lst, t_env *new)
{
	if (!new)
		return;
	if (!lst)
	{
		*lst = *new;
		return;
	}
	t_env *tail = lstlast_env(lst);
	if (tail)
		tail->next = new;
}

t_env	*init_env(char **envp)
{
	t_env	*head = NULL;
	t_env	*current = NULL;
	int i = 0;
	while (envp[i])
	{
		current = lstnew_env(envp[i], 0);
		if (!head)
			head = current;
		else
			lstadd_back_env(head, current);
		i++;
	}
	return head;
}
