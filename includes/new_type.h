/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_type.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:54:21 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 12:45:33 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_TYPE_H
# define NEW_TYPE_H

typedef struct	s_point3
{
	double		x;
	double		y;
	double		z;
}				t_point3;

typedef t_point3	t_vec3;

typedef t_point3	t_color3;

typedef struct	s_range
{
	double		min;
	double		max;
}				t_range;

typedef struct	s_ray
{
	t_point3	orig;
	t_vec3		dir;
}				t_ray;

typedef struct	s_camera
{
	t_point3	origin;
	double		vfov;
	t_point3	vup;
	double		viewport_h;
	double		viewport_w;
	t_vec3		horizontal;
	t_vec3		vertical;
	double		focal_len;
	t_point3	left_bottom;
	double		aspec_ratio;
	t_vec3		lookat;
}				t_camera;

typedef struct	s_rec
{
	t_point3	p;
	double		t;
	t_vec3		n;
	double		t_max;
	double		t_min;
	int			front_face;
	t_color3	albedo;
}				t_rec;

typedef struct	s_sphere
{
	double		radius;
	double		diameter;
	t_point3	center;
	t_color3	albedo;
}				t_sphere;

typedef struct	s_plane
{
	t_point3	orig;
	t_vec3		normal;
	t_color3	albedo;
}				t_plane;

typedef struct	s_square
{
	t_point3	orig;
	t_vec3		normal;
	double		size;
	t_color3	albedo;
}				t_square;

typedef struct	s_cylinder
{
	t_point3	orig;
	t_vec3		normal;
	double		diameter;
	double		height;
	t_color3	albedo;
	t_point3	top_center;
	t_point3	bottom_center;
}				t_cylinder;

typedef struct	s_triangle
{
	t_point3	first;
	t_point3	second;
	t_point3	third;
	t_color3	albedo;
	t_vec3		normal;
}				t_triangle;

typedef struct	s_object
{
	int			type;
	void		*element;
	void		*next;
}				t_object;

typedef struct	s_light
{
	t_point3	orig;
	t_color3	color;
	double		bright_ratio;
}				t_light;

typedef struct	s_img
{
	void		*img;
	char		*addr;
}				t_img;

typedef struct	s_screen
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			endian;
	int			size_l;
	int			bpp;
	t_object	*object;
	t_object	*light;
	t_object	*camera;
	t_object	*img_list;
	t_color3	ambient;
	int			width;
	int			height;
	t_object	*current_img;
}				t_screen;

typedef struct	s_check
{
	int			r;
	int			c;
	int			a;
}				t_check;

#endif
