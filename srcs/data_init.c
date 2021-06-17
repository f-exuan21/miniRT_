/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 03:22:51 by abang             #+#    #+#             */
/*   Updated: 2021/06/17 03:23:16 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void		data_init_3(t_screen *screen, char **arr_split)
{
	if (!ft_strcmp(arr_split[0], "cy"))
	{
		if (!validation_cy(arr_split))
			error("cy(cylinder) has input error");
		parse_cy(screen, arr_split);
	}
	else if (!ft_strcmp(arr_split[0], "tr"))
	{
		if (!validation_tr(arr_split))
			error("tr(triangle) has input error");
		parse_tr(screen, arr_split);
	}
	else if (!ft_strcmp(arr_split[0], "sq"))
	{
		if (!validation_sq(arr_split))
			error("sq(square) has input error");
		parse_sq(screen, arr_split);
	}
	else
		error("Undefined Identifier.");
}

void		data_init_2(t_screen *screen, char **arr_split)
{
	if (!ft_strcmp(arr_split[0], "l"))
	{
		if (!validation_l(arr_split))
			error("l(light) has input error");
		parse_l(screen, arr_split);
	}
	else if (!ft_strcmp(arr_split[0], "sp"))
	{
		if (!validation_sp(arr_split))
			error("sp(sphere) has input error");
		parse_sp(screen, arr_split);
	}
	else if (!ft_strcmp(arr_split[0], "pl"))
	{
		if (!validation_pl(arr_split))
			error("pl(plane) has input error");
		parse_pl(screen, arr_split);
	}
	else
		data_init_3(screen, arr_split);
}

void		data_init(t_screen *screen, char **arr_split, t_check *chk)
{
	if (!ft_strcmp(arr_split[0], "R"))
	{
		if (!validation_r(arr_split))
			error("R(Resolution) has input error");
		chk->r++;
		parse_r(screen, arr_split);
	}
	else if (!ft_strcmp(arr_split[0], "c"))
	{
		if (!validation_c(arr_split))
			error("c(Camera) has input error");
		chk->c++;
		parse_c(screen, arr_split);
	}
	else if (!ft_strcmp(arr_split[0], "A"))
	{
		if (!validation_a(arr_split))
			error("A(Ambient) has input error");
		chk->a++;
		parse_a(screen, arr_split);
	}
	else
		data_init_2(screen, arr_split);
}
