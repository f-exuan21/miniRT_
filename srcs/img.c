/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 18:42:17 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:04:53 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			set_color(t_screen *screen, int i, int j, t_color3 color)
{
	unsigned char	*dst;
	int				r;
	int				g;
	int				b;

	dst = (unsigned char *)screen->addr + \
			(j * screen->size_l + i * (screen->bpp / 8));
	r = color.x * 255.999;
	g = color.y * 255.999;
	b = color.z * 255.999;
	dst[0] = (unsigned char)b;
	dst[1] = (unsigned char)g;
	dst[2] = (unsigned char)r;
	dst[3] = 0;
}

t_color3		ray_color(t_screen *screen, t_ray *r)
{
	double		t;
	t_vec3		unit;
	t_rec		rec;

	rec.t_min = EPSILON;
	rec.t_max = INFINITY;
	if (hit(screen->object, r, &rec))
		return (phong_lighting(screen, &rec, r));
	unit = v_unit(r->dir);
	t = 0.5 * (unit.y + 1.0);
	return (v_plus(v_mul(1.0 - t, vec(1, 1, 1))
				, v_mul(t, vec(0.5, 0.7, 1.0))));
}

t_ray			antialiasing(int i, int j, t_screen *screen, t_camera cam)
{
	t_ray		r;
	double		u;
	double		v;

	u = ((double)i + random_float(1)) / (screen->width - 1);
	v = ((double)j + random_float(1)) / (screen->height - 1);
	r = ray(cam.origin, v_minus(v_plus(v_plus(cam.left_bottom \
								, v_mul(u, cam.horizontal))
								, v_mul(v, cam.vertical)), cam.origin));
	return (r);
}

void			draw_img(t_screen *screen, t_camera cam)
{
	int			i;
	int			j;
	int			k;
	t_color3	color_tmp;
	t_ray		r;

	j = screen->height;
	while (--j >= 0)
	{
		i = 0;
		while (i < screen->width)
		{
			k = 0;
			color_tmp = color(0, 0, 0);
			while (k < SAMPLE_PER_PIXEL)
			{
				r = antialiasing(i, j, screen, cam);
				color_tmp = v_plus(color_tmp, ray_color(screen, &r));
				k++;
			}
			set_color(screen, i, screen->height - 1 - j\
					, v_div(color_tmp, SAMPLE_PER_PIXEL));
			i++;
		}
	}
}

void			setting_img(t_screen *screen)
{
	t_object	*img;
	t_object	*camera;

	img = NULL;
	camera = screen->camera;
	while (camera)
	{
		screen->img = mlx_new_image(screen->mlx, screen->width, screen->height);
		screen->addr = mlx_get_data_addr(screen->img, &screen->bpp \
										, &screen->size_l, &screen->endian);
		add_object(&img, new_object(IMG, new_img(screen->img, screen->addr)));
		camera_setting(camera->element, screen->width, screen->height);
		draw_img(screen, *(t_camera *)camera->element);
		camera = camera->next;
	}
	screen->img_list = img;
	screen->current_img = img;
}
