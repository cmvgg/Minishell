/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:59:47 by alvicina          #+#    #+#             */
/*   Updated: 2023/10/24 09:18:51 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_word(char const *s, char c)
{
	size_t	init;
	size_t	count;
	size_t	final;

	final = 0;
	count = 0;
	init = 0;
	while (s[init] != 0)
	{
		init = final;
		while (s[init] == c && s[init] != 0)
			init++;
		if (s[init] != c && s[init] != 0)
			count++;
		final = init;
		while (s[final] != c && s[final] != 0)
			final++;
		init = final;
	}
	return (count);
}

static char	**ft_free(char **split)
{
	int	limit;

	limit = 0;
	while (split[limit] != 0)
	{
		free(split[limit]);
		split[limit] = NULL;
		limit++;
	}
	free(split);
	split = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	limit;
	size_t	init;
	size_t	final;

	split = malloc((ft_count_word(s, c) + 1) * sizeof(char *));
	if (split == 0)
		return (0);
	limit = -1;
	final = 0;
	while (++limit < ft_count_word(s, c))
	{
		init = final;
		while (s[init] == c && s[init] != 0)
			init++;
		final = init;
		while (s[final] != c && s[final] != 0)
			final++;
		split[limit] = malloc (sizeof(char) * (final - init + 1));
		if (split[limit] == 0)
			return (ft_free(split));
		ft_strlcpy(split[limit], (s + init), final - init + 1);
	}
	split[limit] = 0;
	return (split);
}
/*
int main(void)
{
    char str[] = "hola soy yo_f tr e";
    char c = ' ';

    char **result = ft_split(str, c);
    
    if (result)
    {
        size_t word_count = ft_count_word(str, c);
        printf("El número de palabras es: %zu\n", word_count);
        
        size_t i = 0;
        while (result[i] != (void *)0)
        {
            printf("Palabra %zu: %s\n", i, result[i]);
            i++;
        }
        i = 0;
        while (result[i] != (void *)0)
        {
            free(result[i]);
            i++;
        }
        free(result);
    }
    else
    {
        printf("Error al dividir la cadena.\n");
    }
    
    return (0);
}*/
/*int main(void)
{
	//char str[] = "hola sooy javier";
	//char c = ' ';

	//printf("el numero de palabras son : %zu \n", ft_count_word(str, c));	
	char **resultado = ft_split("Hola soy javier", ' ');
	size_t i = 0;
	if (resultado)
	{
		while (i < ft_count_word("Hola soy javier", ' '))
		{	
			printf("les: %s \n", resultado[i]);
			//free(resultado[i]);
			i++;
		}
	}
	//free(resultado);
	system("leaks -q a.out");
}*/
