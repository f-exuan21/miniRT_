/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 12:34:27 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:05:20 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_point3		v_mul2(t_point3 v1, t_point3 v2)
{
	t_point3	rst;

	rst.x = v1.x * v2.x;
	rst.y = v1.y * v2.y;
	rst.z = v1.z * v2.z;
	return (rst);
}

t_point3		v_minus(t_point3 v1, t_point3 v2)
{
	t_point3	rst;

	rst.x = v1.x - v2.x;
	rst.y = v1.y - v2.y;
	rst.z = v1.z - v2.z;
	return (rst);
}

t_point3		v_div(t_point3 v, double t)
{
	t_point3	rst;

	rst.x = v.x / t;
	rst.y = v.y / t;
	rst.z = v.z / t;
	return (rst);
}

double			v_len(t_vec3 v)
{
	double		len;

	len = sqrt(v_len2(v));
	return (len);
}

t_vec3			v_unit(t_vec3 v)
{
	t_vec3		unit;
	double		len;

	len = v_len(v);
	unit.x = v.x / len;
	unit.y = v.y / len;
	unit.z = v.z / len;
	return (unit);
}
