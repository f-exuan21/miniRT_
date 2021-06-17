/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 20:02:33 by abang             #+#    #+#             */
/*   Updated: 2021/05/03 01:22:22 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_minus_dot(char *s, int *minus_flag, float *flag)
{
	if (*s == '-')
	{
		*minus_flag = 1;
		return (1);
	}
	else if (*s == '.')
	{
		*flag = 0.1;
		return (1);
	}
	return (0);
}

float	ft_atof(char *s)
{
	float	num;
	float	flag;
	int		minus_flag;

	num = 0;
	flag = 0;
	minus_flag = 0;
	while (*s)
	{
		if (check_minus_dot(s, &minus_flag, &flag))
		{
			s++;
			continue ;
		}
		if (flag != 0.0)
		{
			num = num + flag * (*s - '0');
			flag *= 0.1;
		}
		else
			num = num * 10 + (*s - '0');
		s++;
	}
	return (minus_flag == 1 ? -num : num);
}
