/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:06:25 by abang             #+#    #+#             */
/*   Updated: 2020/12/25 01:35:24 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp;
	unsigned char	*tmp2;

	tmp = (unsigned char *)dst;
	tmp2 = (unsigned char *)src;
	if (tmp == tmp2 || len == 0)
		return (dst);
	if (src < dst)
	{
		while (len > 0)
		{
			*(tmp + (len - 1)) = *(tmp2 + (len - 1));
			len--;
		}
	}
	else
	{
		while (len > 0)
		{
			*tmp++ = *tmp2++;
			len--;
		}
	}
	return (dst);
}
