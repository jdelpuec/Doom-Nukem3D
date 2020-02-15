/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendcmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwarin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 14:37:27 by siwarin           #+#    #+#             */
/*   Updated: 2019/03/01 15:12:35 by siwarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strendcmp(const char *s1, const char *s2, size_t n)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	if (n == 0)
		return (0);
	if (s1[i] == '\0' || s2[i] == '\0')
		return (-666);
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	i--;
	j--;
	while (--n && s1[i] == s2[j])
	{
		i--;
		j--;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}
