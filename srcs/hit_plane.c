/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:30:42 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:04:43 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float		plane_solve(t_ray *ray, t_plane *pl, float t_min, float t_max)
{
	t_vec3		n;
	float		denominator;
	float		t;

	n = pl->normal;
	denominator = v_dot(ray->dir, n);
	if (denominator == 0)
		return (INFINITY);
	t = v_dot(n, v_minus(pl->orig, ray->orig)) / denominator;
	if (t <= t_min || t > t_max)
		return (INFINITY);
	return (t);
}

int			hit_plane(t_plane *pl, t_ray *ray, t_rec *rec)
{
	float		t;

	pl->normal = v_unit(pl->normal);
	t = plane_solve(ray, pl, rec->t_min, rec->t_max);
	if (t == INFINITY)
		return (0);
	rec->t = t;
	rec->n = pl->normal;
	rec->p = ray_at(ray, rec->t);
	rec->albedo = pl->albedo;
	set_face_normal(ray, rec);
	return (1);
}
