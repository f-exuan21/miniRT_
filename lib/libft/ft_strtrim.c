/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 11:54:22 by abang             #+#    #+#             */
/*   Updated: 2021/01/07 17:34:42 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_comp(char c, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;
	unsigned int	len;

	str = NULL;
	if (!s1 || !set)
		return (0);
	i = 0;
	while (s1[i] && ft_comp(s1[i], set))
		i++;
	len = ft_strlen(s1);
	if (len != 0)
	{
		len--;
		while (len > 0 && s1[len] && ft_comp(s1[len], set))
			len--;
	}
	j = 0;
	if (!(str = malloc((len - i + 2) * sizeof(char))))
		return (0);
	while (i <= len)
		str[j++] = s1[i++];
	str[j] = '\0';
	return (str);
}
