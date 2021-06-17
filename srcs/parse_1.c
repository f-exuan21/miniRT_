/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 11:38:07 by abang             #+#    #+#             */
/*   Updated: 2021/06/17 02:50:37 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	parse_r(t_screen *screen, char **arr_split)
{
	int		height;
	int		width;
	int		screen_height;
	int		screen_width;

	width = ft_atoi(arr_split[1]);
	height = ft_atoi(arr_split[2]);
	mlx_get_screen_size(screen->mlx, &screen_width, &screen_height);
	if (screen_width < width)
		width = screen_width;
	if (screen_height < height)
		height = screen_height;
	screen->width = width;
	screen->height = height;
}

void	parse_c(t_screen *screen, char **arr_split)
{
	char		**lookfrom_split;
	char		**lookat_split;
	t_point3	lookfrom;
	t_point3	lookat;
	t_camera	*camera;

	lookfrom_split = ft_split(arr_split[1], ',');
	lookat_split = ft_split(arr_split[2], ',');
	lookfrom.x = ft_atof(lookfrom_split[0]);
	lookfrom.y = ft_atof(lookfrom_split[1]);
	lookfrom.z = ft_atof(lookfrom_split[2]);
	lookat.x = ft_atof(lookat_split[0]);
	lookat.y = ft_atof(lookat_split[1]);
	lookat.z = ft_atof(lookat_split[2]);
	camera = new_camera(lookfrom, lookat, ft_atoi(arr_split[3]));
	add_object(&screen->camera, new_object(CAMERA, camera));
	free_arr(lookfrom_split);
	free_arr(lookat_split);
}

void	parse_l(t_screen *screen, char **arr_split)
{
	char		**origin_split;
	char		**color_split;
	t_point3	origin;
	t_color3	color;
	t_light		*light;

	origin_split = ft_split(arr_split[1], ',');
	color_split = ft_split(arr_split[3], ',');
	origin.x = ft_atof(origin_split[0]);
	origin.y = ft_atof(origin_split[1]);
	origin.z = ft_atof(origin_split[2]);
	color.x = ft_atoi(color_split[0]) / (float)255;
	color.y = ft_atoi(color_split[1]) / (float)255;
	color.z = ft_atoi(color_split[2]) / (float)255;
	light = new_light(origin, color, ft_atof(arr_split[2]));
	add_object(&screen->light, new_object(LIGHT, light));
	free_arr(color_split);
	free_arr(origin_split);
}

void	parse_a(t_screen *screen, char **arr_split)
{
	char	**color_split;
	double	ratio;

	color_split = ft_split(arr_split[2], ',');
	ratio = ft_atof(arr_split[1]);
	screen->ambient.x = ft_atoi(color_split[0]) / (float)255 * ratio;
	screen->ambient.y = ft_atoi(color_split[1]) / (float)255 * ratio;
	screen->ambient.z = ft_atoi(color_split[2]) / (float)255 * ratio;
	free_arr(color_split);
}

void	parse_sp(t_screen *screen, char **arr_split)
{
	t_sphere	*sphere;
	char		**center_split;
	char		**color_split;
	t_point3	center;
	t_color3	color;

	center_split = ft_split(arr_split[1], ',');
	center.x = ft_atof(center_split[0]);
	center.y = ft_atof(center_split[1]);
	center.z = ft_atof(center_split[2]);
	color_split = ft_split(arr_split[3], ',');
	color.x = (float)ft_atoi(color_split[0]) / 255;
	color.y = (float)ft_atoi(color_split[1]) / 255;
	color.z = (float)ft_atoi(color_split[2]) / 255;
	sphere = new_sphere(center, ft_atof(arr_split[2]), color);
	add_object(&screen->object, new_object(SPHERE, sphere));
	free_arr(color_split);
	free_arr(center_split);
}
