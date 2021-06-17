/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:47:54 by abang             #+#    #+#             */
/*   Updated: 2021/04/29 23:06:12 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcut(int i, int j, char *src)
{
	char			*tmp;
	int				idx;

	if (!(tmp = malloc(sizeof(char) * (j - i + 1))))
		return (0);
	idx = 0;
	while (i < j)
	{
		tmp[idx] = src[i];
		i++;
		idx++;
	}
	tmp[idx] = '\0';
	return (tmp);
}

t_list	*ft_lst_new(void *content, int status)
{
	t_list	*list;

	if (!(list = (t_list *)malloc(sizeof(t_list))))
		return (0);
	list->content = content;
	list->next = 0;
	list->status = status;
	return (list);
}
