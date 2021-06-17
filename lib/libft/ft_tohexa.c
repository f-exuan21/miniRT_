/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tohexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 18:41:18 by abang             #+#    #+#             */
/*   Updated: 2021/01/25 12:09:19 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tohexa_p(unsigned long ul)
{
	char			*hexa;
	char			*str;
	unsigned int	len;
	unsigned long	tmp;

	hexa = "0123456789abcdef";
	len = (ul == 0 ? 1 : 0);
	tmp = ul;
	while (tmp != 0)
	{
		tmp /= 16;
		len++;
	}
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[0] = '0';
	str[len] = 0;
	while (ul != 0)
	{
		str[--len] = hexa[ul % 16];
		ul /= 16;
	}
	return (str);
}

char	*ft_tohexa_i(unsigned int j, int i)
{
	char			*hexa;
	char			*str;
	unsigned int	len;
	unsigned int	tmp;

	hexa = (i == 0) ? "0123456789abcdef" : "0123456789ABCDEF";
	len = (j == 0 ? 1 : 0);
	tmp = j;
	while (tmp != 0)
	{
		tmp /= 16;
		len++;
	}
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[0] = '0';
	str[len] = 0;
	while (j != 0)
	{
		str[--len] = hexa[j % 16];
		j /= 16;
	}
	return (str);
}
