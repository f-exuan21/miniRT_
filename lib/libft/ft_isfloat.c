/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfloat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 13:15:10 by abang             #+#    #+#             */
/*   Updated: 2021/05/02 18:07:05 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isfloat(char *str)
{
	int		dot_flag;

	dot_flag = 0;
	if (*str == '-')
		str++;
	while (*str)
	{
		if (*str == '.' && !dot_flag)
			dot_flag = 1;
		else if (*str == '.' && dot_flag)
			return (0);
		else
		{
			if (!ft_isdigit(*str))
				return (0);
		}
		str++;
	}
	return (1);
}
