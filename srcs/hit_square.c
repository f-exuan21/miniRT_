/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 13:34:21 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:04:48 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float		square_solve(t_ray *ray, t_square *sq, float t_min, float t_max)
{
	return (plane_solve(ray, (t_plane *)sq, t_min, t_max));
}

int			square_check(t_square *sq, t_ray *ray, float t)
{
	t_vec3	p;
	t_vec3	side_vec;
	t_vec3	center_to_p;
	float	m;
	float	cos1;

	p = ray_at(ray, t);
	if (fabs(sq->normal.y) == 1)
		side_vec = v_cross(sq->normal, point(1, 0, 0));
	else
		side_vec = v_cross(sq->normal, point(0, 1, 0));
	center_to_p = v_minus(p, sq->orig);
	cos1 = fabs(v_dot(side_vec, center_to_p)
				/ (v_len(side_vec) * v_len(center_to_p)));
	if (cos1 >= sqrt(2) / 2)
		m = (sq->size / 2) / cos1;
	else
		m = (sq->size / 2) / (cos(PI / 2 - acos(cos1)));
	if (m >= v_len(center_to_p))
		return (1);
	return (0);
}

int			hit_square(t_square *sq, t_ray *ray, t_rec *rec)
{
	float		t;

	sq->normal = v_unit(sq->normal);
	t = square_solve(ray, sq, rec->t_min, rec->t_max);
	if (t == INFINITY)
		return (0);
	if (square_check(sq, ray, t))
	{
		rec->t = t;
		rec->p = ray_at(ray, t);
		rec->n = sq->normal;
		set_face_normal(ray, rec);
		rec->albedo = sq->albedo;
		return (1);
	}
	return (0);
}
