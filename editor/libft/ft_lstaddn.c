/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 12:19:58 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:52:24 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstaddn(t_list **alst, t_list *new, size_t n)
{
	t_list *lst;

	lst = *alst;
	while (n && lst)
	{
		lst = lst->next;
		n--;
	}
	if (!lst && n > 0)
		return ;
	lst = new;
}
