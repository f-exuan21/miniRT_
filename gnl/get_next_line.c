/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:38:34 by abang             #+#    #+#             */
/*   Updated: 2021/02/21 13:59:26 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void				ft_lst_set(t_list **lst, void *content, int status)
{
	t_list	*tmp;
	char	*str_tmp;

	if ((*lst != NULL) && ((*lst)->status) == 1)
	{
		str_tmp = (*lst)->content;
		(*lst)->content = ft_strjoin(str_tmp, (char *)content);
		(*lst)->status = (status == 1 ? 1 : 0);
		free(str_tmp);
		free(content);
	}
	else
	{
		tmp = ft_lst_new(content, status);
		ft_lstadd_back(lst, tmp);
	}
}

int					get_one_line(t_list **buff, char **line)
{
	t_list			*list;
	int				rst;

	rst = END_OF_LINE;
	if (*buff != NULL)
	{
		*line = ft_strdup((*buff)->content);
		list = *buff;
		if ((*buff)->next != NULL)
			*buff = list->next;
		else
		{
			*buff = 0;
			if (list->status == 0)
				rst = END_OF_FILE;
		}
		free(list->content);
		free(list);
	}
	else
	{
		*line = ft_strdup("");
		rst = END_OF_FILE;
	}
	return (rst);
}

t_list				*transform_struct_list(t_list *buff, char *str)
{
	char			*src;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			src = ft_strcut(j, i, str);
			ft_lst_set(&buff, src, 0);
			j = i + 1;
		}
		i++;
	}
	src = ft_strcut(j, i, str);
	ft_lst_set(&buff, src, 1);
	return (buff);
}

int					get_next_line(int fd, char **line)
{
	static t_list	*buff[OPEN_MAX];
	char			*str;
	int				len;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line || fd >= OPEN_MAX)
		return (ERROR);
	if (!(str = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (ERROR);
	while (buff[fd] == NULL || buff[fd]->status == 1)
	{
		if ((len = (read(fd, str, BUFFER_SIZE))) <= 0)
		{
			if (len < 0)
				return (ERROR);
			if (len == 0 && buff[fd] != NULL)
				buff[fd]->status = 0;
			break ;
		}
		str[len] = '\0';
		buff[fd] = transform_struct_list(buff[fd], str);
	}
	free(str);
	return (get_one_line(&buff[fd], line));
}
