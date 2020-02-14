/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:55:12 by cduverge          #+#    #+#             */
/*   Updated: 2019/07/29 11:13:31 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	remplissage(char const *str, char **tab, char c)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	k = 0;
	while (str[i] == c && str[i])
		i++;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		j = 0;
		while (str[i] != c && str[i])
		{
			tab[k][j] = str[i];
			i++;
			j++;
		}
		if (str[i])
			tab[k][j] = '\0';
		k++;
	}
}

static void	word_lenght(char const *str, size_t *tab, char c)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	k = 0;
	while (str[i] == c && str[i])
		i++;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		j = 0;
		while (str[i] != c && str[i])
		{
			j++;
			i++;
		}
		tab[k] = j;
		k++;
	}
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab_end;
	size_t	word_num;
	size_t	*tab_words;
	size_t	i;

	if (!(s))
		return (NULL);
	word_num = ft_count_words(s, c);
	if (!(tab_words = (size_t *)malloc(sizeof(size_t) * (word_num))))
		return (NULL);
	word_lenght(s, tab_words, c);
	if (!(tab_end = (char **)malloc(sizeof(char *) * (word_num + 1))))
		return (NULL);
	i = 0;
	while (i < word_num)
	{
		if (!(tab_end[i] = (char *)malloc(sizeof(char) * (tab_words[i] + 1))))
			return (NULL);
		i++;
	}
	free(tab_words);
	tab_end[word_num] = NULL;
	remplissage(s, tab_end, c);
	return (tab_end);
}
