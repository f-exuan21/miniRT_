/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:06:50 by abang             #+#    #+#             */
/*   Updated: 2021/06/16 16:20:25 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	char			*tmp;
	char			*tmp2;
	unsigned int	i;
	unsigned int	l;

	tmp = (char *)str;
	tmp2 = (char *)to_find;
	i = 0;
	l = ft_strlen(tmp2);
	if (*tmp2 == '\0')
		return (tmp);
	while ((i + l <= len) || !str)
	{
		if ((*tmp == *tmp2) && !ft_memcmp(tmp, tmp2, l))
			return (tmp);
		tmp++;
		i++;
	}
	return (NULL);
}
