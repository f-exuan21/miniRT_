/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:06:07 by abang             #+#    #+#             */
/*   Updated: 2020/12/22 19:31:41 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *ptr1, const void *ptr2, unsigned int num)
{
	unsigned char	*tmp;
	unsigned char	*tmp2;

	tmp = (unsigned char *)ptr1;
	tmp2 = (unsigned char *)ptr2;
	while (num > 0)
	{
		if (*tmp != *tmp2)
			return ((int)(*tmp - *tmp2));
		tmp++;
		tmp2++;
		num--;
	}
	return (0);
}
