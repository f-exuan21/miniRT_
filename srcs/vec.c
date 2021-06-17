/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 18:20:59 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:05:22 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec3			vec(double x, double y, double z)
{
	t_vec3	rst;

	rst.x = x;
	rst.y = y;
	rst.z = z;
	return (rst);
}

t_point3		point(double x, double y, double z)
{
	t_point3	rst;

	rst.x = x;
	rst.y = y;
	rst.z = z;
	return (rst);
}

t_color3		color(double x, double y, double z)
{
	t_color3	rst;

	rst.x = x;
	rst.y = y;
	rst.z = z;
	return (rst);
}

t_point3		v_plus(t_point3 v1, t_point3 v2)
{
	t_point3	rst;

	rst.x = v1.x + v2.x;
	rst.y = v1.y + v2.y;
	rst.z = v1.z + v2.z;
	return (rst);
}

t_point3		v_mul(double t, t_point3 v)
{
	t_point3	rst;

	rst.x = t * v.x;
	rst.y = t * v.y;
	rst.z = t * v.z;
	return (rst);
}
