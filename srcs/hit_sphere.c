/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 21:13:20 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:04:45 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int				hit_sphere(t_sphere *sp, t_ray *r, t_rec *rec)
{
	t_vec3		oc;
	double		element[3];
	double		discriminant;
	double		formula;

	oc = v_minus(r->orig, sp->center);
	element[0] = v_len2(r->dir);
	element[1] = v_dot(oc, r->dir);
	element[2] = v_len2(oc) - sp->radius * sp->radius;
	discriminant = element[1] * element[1] - element[0] * element[2];
	if (discriminant < 0)
		return (0);
	formula = (-element[1] - sqrt(discriminant)) / element[0];
	if (formula < rec->t_min || formula >= rec->t_max)
	{
		formula = (-element[1] + sqrt(discriminant)) / element[0];
		if (formula < rec->t_min || formula >= rec->t_max)
			return (0);
	}
	rec->t = formula;
	rec->p = ray_at(r, formula);
	rec->n = v_div(v_minus(rec->p, sp->center), sp->radius);
	rec->albedo = sp->albedo;
	set_face_normal(r, rec);
	return (1);
}
