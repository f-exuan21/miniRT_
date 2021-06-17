/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 18:45:14 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:04:52 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int				hit_obj(t_object *obj, t_ray *r, t_rec *rec)
{
	int			rst;

	rst = 0;
	if (obj->type == SPHERE)
		rst = hit_sphere((t_sphere *)obj->element, r, rec);
	else if (obj->type == CYLINDER)
		rst = hit_cylinder((t_cylinder *)obj->element, r, rec);
	else if (obj->type == PLANE)
		rst = hit_plane((t_plane *)obj->element, r, rec);
	else if (obj->type == SQUARE)
		rst = hit_square((t_square *)obj->element, r, rec);
	else if (obj->type == TRIANGLE)
		rst = hit_triangle((t_triangle *)obj->element, r, rec);
	return (rst);
}

int				hit(t_object *obj, t_ray *r, t_rec *rec)
{
	int			hit_anything;
	t_rec		tmp_rec;

	tmp_rec = *rec;
	hit_anything = 0;
	while (obj)
	{
		if (hit_obj(obj, r, &tmp_rec))
		{
			hit_anything = 1;
			tmp_rec.t_max = tmp_rec.t;
			*rec = tmp_rec;
		}
		obj = obj->next;
	}
	return (hit_anything);
}
