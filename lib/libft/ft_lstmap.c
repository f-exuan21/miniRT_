/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 17:24:07 by abang             #+#    #+#             */
/*   Updated: 2020/12/23 17:45:08 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*rst;

	if (!(rst = ft_lstnew((*f)(lst->content))))
		return (0);
	tmp = rst;
	lst = lst->next;
	while (lst)
	{
		if (!(tmp->next = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&rst, del);
			return (0);
		}
		tmp = tmp->next;
		lst = lst->next;
	}
	return (rst);
}
