/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 13:35:07 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:05:01 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_sphere	*new_sphere(t_point3 center, double diameter, t_color3 albedo)
{
	t_sphere	*sp;

	if (!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
		return (0);
	sp->center = center;
	sp->diameter = diameter;
	sp->radius = diameter / 2.0;
	sp->albedo = albedo;
	return (sp);
}

t_light		*new_light(t_point3 orig, t_color3 color, double ratio)
{
	t_light		*light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		return (0);
	light->orig = orig;
	light->color = color;
	light->bright_ratio = ratio;
	return (light);
}

t_camera	*new_camera(t_point3 orig, t_vec3 dir, double vfov)
{
	t_camera	*cam;

	if (!(cam = (t_camera *)malloc(sizeof(t_camera))))
		return (0);
	cam->origin = orig;
	cam->lookat = dir;
	cam->vfov = vfov;
	return (cam);
}

t_cylinder	*new_cylinder(t_point3 orient, t_vec3 coord, float diameter)
{
	t_cylinder	*cylinder;

	if (!(cylinder = malloc(sizeof(t_cylinder))))
		return (0);
	cylinder->normal = coord;
	cylinder->orig = orient;
	cylinder->diameter = diameter;
	return (cylinder);
}

void		new_cylinder2(t_cylinder *cylinder, float height, t_color3 albedo)
{
	cylinder->height = height;
	cylinder->albedo = albedo;
	cylinder->top_center = v_plus(cylinder->orig, \
								v_mul(cylinder->height / 2, \
								v_unit(cylinder->normal)));
	cylinder->bottom_center = v_minus(cylinder->orig, \
								v_mul(cylinder->height / 2, \
								v_unit(cylinder->normal)));
}
