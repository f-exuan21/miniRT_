/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 12:34:05 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:05:18 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double			v_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double			v_len2(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_point3		v_min(t_vec3 v, t_vec3 l)
{
	if (v.x > l.x)
		v.x = l.x;
	if (v.y > l.y)
		v.y = l.y;
	if (v.z > l.z)
		v.z = l.z;
	return (v);
}

t_vec3			v_cross(t_vec3 u, t_vec3 v)
{
	t_vec3		target;

	target.x = u.y * v.z - u.z * v.y;
	target.y = u.z * v.x - u.x * v.z;
	target.z = u.x * v.y - u.y * v.x;
	return (target);
}

t_vec3			reflect(t_vec3 v, t_vec3 n)
{
	return (v_minus(v, v_mul(2 * v_dot(v, n), n)));
}
