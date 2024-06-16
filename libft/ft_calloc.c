/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:16:24 by jllarena          #+#    #+#             */
/*   Updated: 2023/10/02 17:39:46 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*dst;

	dst = malloc(size * count);
	if (!dst)
	{
		return (0);
	}
	ft_bzero(dst, size * count);
	return (dst);
}
/* 
int main(void)
{
   printf("\n---- calloc ----\n");
   int *calloc_test;
   calloc_test = (int *)ft_calloc(6, sizeof(int));
   printf("Calloc an array of 6 int\n    ");
   for(int i = 0; i < 6; i++)
       printf("%d ", calloc_test[i]);
   printf("\n");
   free(calloc_test);
}
*/
