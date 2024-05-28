/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:59:32 by jllarena          #+#    #+#             */
/*   Updated: 2023/10/23 11:19:21 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(*del)(lst -> content);
	free (lst);
}

/*
void del_free(void *data)
{
    free(data);
}
int main() {
   
  	t_list  *nodo1;
    t_list  *nodo2;
    t_list  *nodo3;
	char str_last1[] = "nodo1";
	char str_last2[] = "nodo2";	
	char str_last3[] = "nodo3";

    nodo1 = malloc(sizeof(t_list) * 1);
    nodo2 = malloc(sizeof(t_list) * 1);
    nodo3 = malloc(sizeof(t_list) * 1);

    nodo1 -> next = nodo2;
    nodo2 -> next = nodo3;

	nodo1 -> content = (void *)str_last1;
	nodo2 -> content = (void *)str_last2;	
    nodo3 -> content = (void *)str_last3;


    printf("Contenido de la lista antes de la eliminación:\n");
    t_list *current = nodo1;
    while (current)
    {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }

    ft_lstdelone(nodo2, del_free);

    printf("\nContenido de la lista después de la eliminación:\n");
    current = nodo1;
    while (current)
	{
        printf("%s\n", (char *)current->content);
        current = current->next;
    }

    return 0;
}*/