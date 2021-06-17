/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:02:24 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:05:11 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int			validation_r(char **str_arr)
{
	char	*tmp;

	if (arr_len(str_arr) != 3)
		return (0);
	tmp = str_arr[1];
	while (*tmp)
	{
		if (!ft_isdigit(*tmp))
			return (0);
		tmp++;
	}
	tmp = str_arr[2];
	while (*tmp)
	{
		if (!ft_isdigit(*tmp))
			return (0);
		tmp++;
	}
	return (1);
}

int			validation_c(char **str_arr)
{
	char	*tmp;

	if (arr_len(str_arr) != 4)
		return (0);
	if (!validation_point(str_arr[1]) || !validation_vec(str_arr[2]))
		return (0);
	tmp = str_arr[3];
	while (*tmp)
	{
		if (!ft_isdigit(*tmp))
			return (0);
		tmp++;
	}
	return (1);
}

int			validation_a(char **str_arr)
{
	float	tmp;

	if (arr_len(str_arr) != 3)
		return (0);
	if (!ft_isfloat(str_arr[1]))
		return (0);
	if ((tmp = ft_atof(str_arr[1])) < 0.0 || tmp > 1.0)
		return (0);
	if (!validation_rgb(str_arr[2]))
		return (0);
	return (1);
}

int			validation_sp(char **str_arr)
{
	if (arr_len(str_arr) != 4)
		return (0);
	if (!validation_point(str_arr[1]))
		return (0);
	if (!ft_isfloat(str_arr[2]))
		return (0);
	if (!validation_rgb(str_arr[3]))
		return (0);
	return (1);
}

int			validation_l(char **str_arr)
{
	float	tmp;

	if (arr_len(str_arr) != 4)
		return (0);
	if (!validation_point(str_arr[1]))
		return (0);
	if ((tmp = ft_atof(str_arr[2])) < 0 || tmp > 1)
		return (0);
	if (!validation_rgb(str_arr[3]))
		return (0);
	return (1);
}
