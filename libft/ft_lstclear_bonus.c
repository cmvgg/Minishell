/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:59:02 by jllarena          #+#    #+#             */
/*   Updated: 2023/10/23 11:13:36 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*new;
	t_list	*next;

	new = *lst;
	if (!*lst || !del)
		return ;
	while (new != NULL)
	{
		next = new ->next;
		(*del)(new->content);
		free(new);
		new = next;
	}
	*lst = NULL;
}
/*
void del_delete(void* data)
{
    if (data == (void *)0)
		return ;
	free (data);
}

int main(void)
{
	t_list *element;
	element = malloc(sizeof(t_list));
	int num = 8;
	int *ptr_num = malloc(sizeof(int));
	*ptr_num = num;

	element ->content = ptr_num;
	ft_lstclear(&element, &del_delete);

	if (element == (void *)0) 
	{
        printf("Elemento eliminado con éxito.\n");
    }
	else
	{
        printf("Error: el elemento no se eliminó correctamente.\n");
    }
}*/