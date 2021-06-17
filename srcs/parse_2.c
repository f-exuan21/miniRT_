/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:33:29 by abang             #+#    #+#             */
/*   Updated: 2021/06/17 02:50:55 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	parse_pl(t_screen *screen, char **arr_split)
{
	t_plane		*plane;
	char		**orig;
	char		**normal;
	char		**albedo;

	orig = ft_split(arr_split[1], ',');
	normal = ft_split(arr_split[2], ',');
	albedo = ft_split(arr_split[3], ',');
	plane = new_plane(point(ft_atof(orig[0]) \
								, ft_atof(orig[1]) \
								, ft_atof(orig[2])) \
					, vec(ft_atof(normal[0]) \
								, ft_atof(normal[1]) \
								, ft_atof(normal[2])) \
					, color((float)ft_atoi(albedo[0]) / 255 \
								, (float)ft_atoi(albedo[1]) / 255\
								, (float)ft_atoi(albedo[2]) / 255));
	add_object(&screen->object, new_object(PLANE, plane));
	free_arr(orig);
	free_arr(normal);
	free_arr(albedo);
}

void	parse_sq(t_screen *screen, char **arr_split)
{
	t_square	*sq;
	char		**orig;
	char		**normal;
	char		**albedo;

	orig = ft_split(arr_split[1], ',');
	normal = ft_split(arr_split[2], ',');
	albedo = ft_split(arr_split[4], ',');
	sq = new_square(point(ft_atof(orig[0]) \
							, ft_atof(orig[1]), ft_atof(orig[2])) \
					, vec(ft_atof(normal[0]) \
							, ft_atof(normal[1]), ft_atof(normal[2])) \
					, ft_atof(arr_split[3]) \
					, color((float)ft_atoi(albedo[0]) / 255 \
							, (float)ft_atoi(albedo[1]) / 255 \
							, (float)ft_atoi(albedo[2]) / 255));
	add_object(&screen->object, new_object(SQUARE, sq));
	free_arr(orig);
	free_arr(normal);
	free_arr(albedo);
}

void	parse_cy(t_screen *screen, char **arr_split)
{
	t_cylinder	*cy;
	char		**coord;
	char		**orient;
	char		**albedo;

	coord = ft_split(arr_split[2], ',');
	orient = ft_split(arr_split[1], ',');
	albedo = ft_split(arr_split[5], ',');
	cy = new_cylinder(point(ft_atof(orient[0]) \
								, ft_atof(orient[1]) \
								, ft_atof(orient[2])) \
					, vec(ft_atof(coord[0]) \
								, ft_atof(coord[1]) \
								, ft_atof(coord[2])) \
					, ft_atof(arr_split[3]));
	new_cylinder2(cy, ft_atof(arr_split[4]) \
					, color((float)ft_atoi(albedo[0]) / 255 \
								, (float)ft_atoi(albedo[1]) / 255 \
								, (float)ft_atoi(albedo[2]) / 255));
	add_object(&screen->object, new_object(CYLINDER, cy));
	free_arr(coord);
	free_arr(orient);
	free_arr(albedo);
}

void	parse_tr(t_screen *screen, char **arr_split)
{
	t_triangle	*tri;
	char		**first;
	char		**second;
	char		**third;
	char		**albedo;

	first = ft_split(arr_split[1], ',');
	second = ft_split(arr_split[2], ',');
	third = ft_split(arr_split[3], ',');
	albedo = ft_split(arr_split[4], ',');
	tri = new_triangle(point(ft_atof(first[0]) \
								, ft_atof(first[1]), ft_atof(first[2])) \
					, point(ft_atof(second[0]) \
								, ft_atof(second[1]), ft_atof(second[2])) \
					, point(ft_atof(third[0]) \
								, ft_atof(third[1]), ft_atof(third[2])) \
					, color((float)ft_atoi(albedo[0]) / 255 \
								, (float)ft_atoi(albedo[1]) / 255 \
								, (float)ft_atoi(albedo[2]) / 255));
	add_object(&screen->object, new_object(TRIANGLE, tri));
	free_arr(first);
	free_arr(second);
	free_arr(third);
	free_arr(albedo);
}
