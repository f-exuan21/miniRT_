/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 23:09:42 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:04:41 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int			check_cap(t_ray *ray, float t, t_point3 center, float radius)
{
	t_point3	p;
	t_vec3		tmp;

	p = ray_at(ray, t);
	tmp = v_minus(p, center);
	if (v_len(tmp) > radius)
		return (1);
	return (0);
}

float		cap_solve(t_ray *ray, t_cylinder *cy, float t_min, float t_max)
{
	float	top_t;
	float	bottom_t;
	float	denominator;
	t_vec3	top_oc;
	t_vec3	bottom_oc;

	denominator = v_dot(ray->dir, cy->normal);
	if (denominator == 0)
		return (INFINITY);
	top_oc = v_minus(cy->top_center, ray->orig);
	top_t = v_dot(top_oc, cy->normal) / denominator;
	if (check_cap(ray, top_t, cy->top_center, cy->diameter / 2))
		top_t = INFINITY;
	bottom_oc = v_minus(cy->bottom_center, ray->orig);
	bottom_t = v_dot(bottom_oc, cy->normal) / denominator;
	if (check_cap(ray, bottom_t, cy->bottom_center, cy->diameter / 2))
		bottom_t = INFINITY;
	if (top_t <= t_min || top_t > t_max)
		top_t = INFINITY;
	if (bottom_t <= t_min || bottom_t > t_max)
		bottom_t = INFINITY;
	if (top_t < bottom_t)
		return (top_t);
	else
		return (bottom_t);
}

double		cylinder_solve(t_ray *ray, t_cylinder *cy, float t_min, float t_max)
{
	float		discriminant;
	float		a;
	float		b;
	float		t;
	t_point3	hit_point;

	discriminant = cy_discriminant(ray, cy, &a, &b);
	if (discriminant < 0)
		return (INFINITY);
	t = (-b - sqrt(discriminant)) / a;
	hit_point = ray_at(ray, t);
	if (v_dot(cy->normal, v_minus(hit_point, cy->top_center)) > 0)
		return (INFINITY);
	if (v_dot(cy->normal, v_minus(hit_point, cy->bottom_center)) < 0)
		return (INFINITY);
	if (t <= t_min || t > t_max)
		return (INFINITY);
	return (t);
}

void		set_cy_rec(t_ray *ray, t_cylinder *cy, t_rec *rec, float t[2])
{
	t_point3	center;
	t_vec3		normal;

	if (t[0] < t[1])
	{
		rec->t = t[0];
		rec->p = ray_at(ray, rec->t);
		center = v_mul(v_dot(v_minus(rec->p, cy->orig), cy->normal) \
						, cy->normal);
		center = v_plus(cy->orig, center);
		normal = v_unit(v_minus(rec->p, center));
		rec->n = normal;
	}
	else
	{
		rec->t = t[1];
		rec->p = ray_at(ray, rec->t);
		rec->n = cy->normal;
	}
	rec->albedo = cy->albedo;
}

int			hit_cylinder(t_cylinder *cy, t_ray *ray, t_rec *rec)
{
	float		cy_t;
	float		cap_t;
	float		t[2];

	cy->normal = v_unit(cy->normal);
	cy_t = cylinder_solve(ray, cy, rec->t_min, rec->t_max);
	cap_t = cap_solve(ray, cy, rec->t_min, rec->t_max);
	if (cap_t == INFINITY && cy_t == INFINITY)
		return (0);
	t[0] = cy_t;
	t[1] = cap_t;
	set_cy_rec(ray, cy, rec, t);
	set_face_normal(ray, rec);
	return (1);
}
