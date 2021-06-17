/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 20:34:02 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:05:15 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		validation_pl(char **arr_split)
{
	if (arr_len(arr_split) != 4)
		return (0);
	if (!validation_point(arr_split[1]))
		return (0);
	if (!validation_vec(arr_split[2]))
		return (0);
	if (!validation_rgb(arr_split[3]))
		return (0);
	return (1);
}

int		validation_sq(char **arr_split)
{
	if (arr_len(arr_split) != 5)
		return (0);
	if (!validation_point(arr_split[1]))
		return (0);
	if (!validation_vec(arr_split[2]))
		return (0);
	if (!ft_isfloat(arr_split[3]))
		return (0);
	if (!validation_rgb(arr_split[4]))
		return (0);
	return (1);
}

int		validation_cy(char **arr_split)
{
	if (arr_len(arr_split) != 6)
		return (0);
	if (!validation_point(arr_split[1]))
		return (0);
	if (!validation_vec(arr_split[2]))
		return (0);
	if (!ft_isfloat(arr_split[3]))
		return (0);
	if (!ft_isfloat(arr_split[4]))
		return (0);
	if (!validation_rgb(arr_split[5]))
		return (0);
	return (1);
}

int		validation_tr(char **arr_split)
{
	if (arr_len(arr_split) != 5)
		return (0);
	if (!validation_point(arr_split[1]))
		return (0);
	if (!validation_point(arr_split[2]))
		return (0);
	if (!validation_point(arr_split[3]))
		return (0);
	if (!validation_rgb(arr_split[4]))
		return (0);
	return (1);
}
