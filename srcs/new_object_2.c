/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_object_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 12:32:48 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:04:59 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_triangle	*new_triangle(t_point3 first, t_point3 second, t_point3 third \
						, t_color3 albedo)
{
	t_triangle	*triangle;

	if (!(triangle = malloc(sizeof(t_triangle))))
		return (0);
	triangle->first = first;
	triangle->second = second;
	triangle->third = third;
	triangle->albedo = albedo;
	return (triangle);
}

t_plane		*new_plane(t_point3 point, t_vec3 normal, t_color3 albedo)
{
	t_plane		*plane;

	if (!(plane = malloc(sizeof(t_plane))))
		return (0);
	plane->orig = point;
	plane->normal = normal;
	plane->albedo = albedo;
	return (plane);
}

t_square	*new_square(t_point3 point, t_vec3 normal \
						, float size, t_color3 albedo)
{
	t_square	*square;

	if (!(square = malloc(sizeof(t_square))))
		return (0);
	square->orig = point;
	square->normal = normal;
	square->size = size;
	square->albedo = albedo;
	return (square);
}

t_img		*new_img(void *img, char *addr)
{
	t_img	*img_;

	if (!(img_ = (t_img *)malloc(sizeof(t_img))))
		return (0);
	img_->img = img;
	img_->addr = addr;
	return (img_);
}
