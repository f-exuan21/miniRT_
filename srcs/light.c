/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 18:40:14 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:04:55 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int				in_shadow(t_object *objs, t_ray *light_r)
{
	t_rec		rec;

	rec.t_min = 0;
	rec.t_max = 1;
	if (hit(objs, light_r, &rec))
		return (1);
	return (0);
}

t_color3		specular(t_ray *r, t_light *light, t_rec *rec, t_vec3 light_dir)
{
	t_color3	specular;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	double		spec;

	view_dir = v_unit(v_mul(-1, r->dir));
	reflect_dir = reflect(v_mul(-1, light_dir), rec->n);
	spec = pow(fmax(v_dot(view_dir, reflect_dir), 0.0), KSN);
	specular = v_mul(spec, v_mul(KS, light->color));
	return (specular);
}

t_color3		diffuse(t_light *light, t_rec *rec, t_vec3 light_dir)
{
	double		kd;
	t_color3	diffuse;

	kd = fmax(v_dot(rec->n, light_dir), 0.0);
	diffuse = v_mul(kd, light->color);
	return (diffuse);
}

t_color3		get_point_light(t_screen *screen, t_ray *r\
								, t_light *light, t_rec *rec)
{
	t_vec3		light_dir;
	double		brightness;
	double		light_len;
	t_ray		light_ray;

	light_dir = v_minus(light->orig, rec->p);
	light_len = v_len(light_dir);
	light_ray = ray(v_plus(rec->p, v_mul(EPSILON, rec->n)), light_dir);
	if (in_shadow(screen->object, &light_ray))
		return (color(0, 0, 0));
	brightness = light->bright_ratio * LUMEN;
	light_dir = v_unit(light_dir);
	return (v_mul(brightness, v_plus(specular(r, light, rec, light_dir) \
									, diffuse(light, rec, light_dir))));
}

t_color3		phong_lighting(t_screen *screen, t_rec *rec, t_ray *r)
{
	t_color3	light_color;
	t_object	*lights;

	light_color = color(0, 0, 0);
	lights = screen->light;
	while (lights)
	{
		light_color = v_plus(light_color\
							, get_point_light(screen, r, lights->element, rec));
		lights = lights->next;
	}
	light_color = v_plus(light_color, screen->ambient);
	return (v_min(v_mul2(light_color, rec->albedo), color(1, 1, 1)));
}
