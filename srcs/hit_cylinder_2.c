/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 08:24:17 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:04:39 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float		cy_discriminant(t_ray *ray, t_cylinder *cy, float *a, float *b)
{
	t_vec3		w;
	t_vec3		v;
	t_vec3		oc;
	float		c;
	float		discriminant;

	oc = v_minus(ray->orig, cy->orig);
	v = v_cross(ray->dir, cy->normal);
	w = v_cross(oc, cy->normal);
	*a = v_dot(v, v);
	*b = v_dot(v, w);
	c = v_dot(w, w) - pow(cy->diameter / 2, 2);
	discriminant = *b * *b - *a * c;
	return (discriminant);
}
