/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:06:53 by abang             #+#    #+#             */
/*   Updated: 2020/12/25 03:29:07 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	int		len;

	len = ft_strlen(s);
	tmp = (char *)s + len;
	if (*tmp == '\0' && c == '\0')
		return (tmp);
	tmp--;
	while (len > 0)
	{
		if (*tmp == c)
			return (tmp);
		tmp--;
		len--;
	}
	return (NULL);
}
