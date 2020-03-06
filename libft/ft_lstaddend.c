/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 12:59:23 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:50:01 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstaddend(t_list **alst, t_list *new)
{
	t_list *lst;

	lst = *alst;
	if (lst->next == NULL)
		return ;
	while (lst)
	{
		new->next = lst;
		lst->next = lst;
	}
	lst = new;
}
