/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 03:21:17 by abang             #+#    #+#             */
/*   Updated: 2021/06/17 14:57:07 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			split_len(char *target, char *s)
{
	int		len;
	int		flag;
	char	*tmp;

	tmp = target;
	flag = 0;
	len = 0;
	while (*tmp)
	{
		if (ft_strchr(s, *tmp) != NULL)
		{
			if (flag == 0)
				len++;
			flag = 1;
		}
		else
			flag = 0;
		tmp++;
	}
	return (len + 1);
}

int			split(char *tmp, char *s, char **rst)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (1)
	{
		if (ft_strchr(s, *tmp) != NULL)
		{
			if (i != 0)
			{
				if (!(rst[cnt] = malloc(sizeof(char) * (i + 1))))
					return (0);
				ft_strlcpy(rst[cnt], tmp - i, i + 1);
				cnt++;
			}
			i = -1;
		}
		if (*tmp == '\0')
			break ;
		i++;
		tmp++;
	}
	return (1);
}

char		**ft_splitstr(char *target, char *s)
{
	int		len;
	char	*tmp;
	char	**rst;

	tmp = ft_strtrim(target, s);
	if (*tmp == '\0')
	{
		free(tmp);
		return (0);
	}
	len = split_len(tmp, s);
	if (len == 1 || !(rst = malloc(sizeof(char *) * len + 1)))
		return (0);
	rst[len] = NULL;
	if (!split(tmp, s, rst))
		return (0);
	free(tmp);
	return (rst);
}
