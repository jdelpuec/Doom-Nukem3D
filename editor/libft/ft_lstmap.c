/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 01:31:45 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 16:52:39 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*p;
	t_list	*p2;

	new = NULL;
	if (!lst || !f)
		return (NULL);
	p2 = f(lst);
	if ((new = ft_lstnew(p2->content, p2->content_size)))
	{
		p = new;
		lst = lst->next;
		while (lst)
		{
			p2 = f(lst);
			if (!(p->next = ft_lstnew(p2->content, p2->content_size)))
				return (NULL);
			p = p->next;
			lst = lst->next;
		}
	}
	return (new);
}
