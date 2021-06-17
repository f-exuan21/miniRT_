/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 11:33:51 by abang             #+#    #+#             */
/*   Updated: 2020/12/22 19:08:10 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, unsigned int num)
{
	unsigned char	*tmp;
	unsigned char	*tmp2;
	unsigned int	i;

	tmp = (unsigned char *)dest;
	tmp2 = (unsigned char *)src;
	i = 0;
	if (tmp == tmp2)
		return (dest);
	while (i < num)
	{
		tmp[i] = tmp2[i];
		i++;
	}
	return (dest);
}
