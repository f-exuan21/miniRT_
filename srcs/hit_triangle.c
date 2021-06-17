/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:41:58 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:04:50 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float		solve_triangle(t_ray *ray, t_triangle *tr, float t_min, float t_max)
{
	t_plane	pl;

	pl.orig = tr->first;
	pl.normal = tr->normal;
	pl.albedo = tr->albedo;
	return (plane_solve(ray, &pl, t_min, t_max));
}

int			check_range(t_vec3 w, t_vec3 v, t_vec3 u, t_vec3 n)
{
	float	x;
	float	y;
	t_vec3	up;
	t_vec3	vp;

	up = v_cross(n, u);
	vp = v_cross(n, v);
	x = v_dot(w, vp) / v_dot(u, vp);
	y = v_dot(w, up) / v_dot(v, up);
	if (0 <= x && x <= 1 && 0 <= y && y <= 1 && x + y <= 1)
		return (1);
	return (0);
}

int			check_triangle(t_ray *ray, t_triangle *tr, float t)
{
	t_vec3	w;
	t_vec3	u;
	t_vec3	v;

	w = v_minus(ray_at(ray, t), tr->first);
	u = v_minus(tr->second, tr->first);
	v = v_minus(tr->third, tr->first);
	return (check_range(w, v, u, tr->normal));
}

int			hit_triangle(t_triangle *tr, t_ray *ray, t_rec *rec)
{
	float		t;

	tr->normal = v_unit(v_cross(v_minus(tr->second, tr->first) \
								, v_minus(tr->third, tr->first)));
	t = solve_triangle(ray, tr, rec->t_min, rec->t_max);
	if (t == INFINITY)
		return (0);
	if (check_triangle(ray, tr, t))
	{
		rec->t = t;
		rec->n = tr->normal;
		rec->albedo = tr->albedo;
		rec->p = ray_at(ray, t);
		set_face_normal(ray, rec);
		return (1);
	}
	return (0);
}
