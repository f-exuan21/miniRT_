/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 19:23:16 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:05:08 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_ray			ray(t_point3 orig, t_vec3 dir)
{
	t_ray		ray;

	ray.orig = orig;
	ray.dir = dir;
	return (ray);
}

t_point3		ray_at(t_ray *ray, double t)
{
	t_point3	at;

	at = v_plus(ray->orig, v_mul(t, ray->dir));
	return (at);
}
