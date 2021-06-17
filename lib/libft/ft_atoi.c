/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:05:21 by abang             #+#    #+#             */
/*   Updated: 2020/12/26 16:10:45 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_chkmax(unsigned long long n, int minus)
{
	if (n > LLONG_MAX && minus == 0)
		return (-1);
	else if (n - 1 > (LLONG_MAX) && minus == 1)
		return (0);
	else
		return (1);
}

int		ft_atoi(const char *str)
{
	long long		rst;
	int				minus;
	int				chk;

	rst = 0;
	minus = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		minus = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		rst = rst * 10 + (*str - '0');
		str++;
	}
	chk = ft_chkmax(rst, minus);
	if (chk == -1 || chk == 0)
		return (chk);
	return (minus ? -rst : rst);
}
