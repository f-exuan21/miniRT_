/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 09:40:56 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:04:06 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			camera_setting(t_camera *cam, int width, int height)
{
	double	theta;
	double	h;
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;

	theta = degrees_to_radians(cam->vfov);
	h = tan(theta / 2);
	cam->aspec_ratio = (double)width / height;
	cam->viewport_h = 2 * h;
	cam->viewport_w = cam->aspec_ratio * cam->viewport_h;
	w = v_unit(v_mul(-1, cam->lookat));
	if (cam->lookat.x == 0 && cam->lookat.y != 0 && cam->lookat.z == 0)
		cam->vup = vec(0, 0, -1);
	else
		cam->vup = vec(0, 1, 0);
	u = v_unit(v_cross(cam->vup, w));
	v = v_cross(w, u);
	cam->horizontal = v_mul(cam->viewport_w, u);
	cam->vertical = v_mul(cam->viewport_h, v);
	cam->left_bottom = v_minus(v_minus(
							v_minus(cam->origin, v_div(cam->horizontal, 2))
							, v_div(cam->vertical, 2)), w);
}
