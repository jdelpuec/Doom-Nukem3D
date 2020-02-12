/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwarin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:38:50 by siwarin           #+#    #+#             */
/*   Updated: 2018/11/22 12:38:35 by siwarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*t;
	t_list	*a;

	if (!alst)
		return ;
	a = *alst;
	while (a != NULL)
	{
		t = a->next;
		del(a, a->content_size);
		a = t;
	}
	*alst = NULL;
}
