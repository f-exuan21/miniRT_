/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 12:42:31 by abang             #+#    #+#             */
/*   Updated: 2021/06/17 12:49:42 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "get_next_line.h"
# include "new_type.h"
# include "mlx.h"
# include <float.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>

# define EPSILON 1e-4
# define LUMEN 3
# define SAMPLE_PER_PIXEL 100
# define PI 3.14159265359
# define ESC 53
# define N 45
# define SPHERE 2
# define PLANE 3
# define CYLINDER 4
# define SQUARE 5
# define TRIANGLE 6
# define LIGHT 10
# define CAMERA 11
# define IMG 12
# define KSN 64
# define KS 0.5

/*
** common
*/

void			set_face_normal(t_ray *r, t_rec *rec);
float			random_float(float max);
float			random_float_2(void);
float			degrees_to_radians(float degree);
int				arr_len(char **str_arr);
float			clamp(float x);
void			error(char *str);

/*
** file
*/

void			read_file(t_screen *screen, char *file_name);

/*
** hit
*/

int				hit_sphere(t_sphere *sp, t_ray *r, t_rec *rec);
float			plane_solve(t_ray *ray, t_plane *pl, float t_min, float t_max);
int				hit_cylinder(t_cylinder *cy, t_ray *ray, t_rec *rec);
int				hit_plane(t_plane *pl, t_ray *ray, t_rec *rec);
int				hit_square(t_square *sq, t_ray *ray, t_rec *rec);
int				hit_triangle(t_triangle *tr, t_ray *ray, t_rec *rec);
int				hit_obj(t_object *obj, t_ray *r, t_rec *rec);
int				hit(t_object *obj, t_ray *r, t_rec *rec);
float			cy_discriminant(t_ray *ray, t_cylinder *cy, float *a, float *b);

/*
** setting_camera
*/

void			camera_setting(t_camera *cam, int width, int height);

/*
** loading image
*/

void			set_color(t_screen *screen, int i, int j, t_color3 color);
t_color3		ray_color(t_screen *screen, t_ray *r);
void			draw_img(t_screen *screen, t_camera cam);
void			setting_img(t_screen *screen);

/*
** light
*/

t_color3		phong_lighting(t_screen *screen, t_rec *rec, t_ray *r);
t_color3		get_point_light(t_screen *screen, t_ray *r \
								, t_light *light, t_rec *rec);
int				in_shadow(t_object *objs, t_ray *light_r);

/*
** allocates new object
*/

t_sphere		*new_sphere(t_point3 center, double diameter, t_color3 albedo);
t_light			*new_light(t_point3 orig, t_color3 color, double ratio);
t_camera		*new_camera(t_point3 orig, t_vec3 dir, double vfov);
t_img			*new_img(void *img, char *addr);
t_cylinder		*new_cylinder(t_point3 orient, t_vec3 coord, float diameter);
void			new_cylinder2(t_cylinder *cylinder, float height \
							, t_color3 albedo);
t_triangle		*new_triangle(t_point3 first, t_point3 second \
							, t_point3 third, t_color3 albedo);
t_plane			*new_plane(t_point3 point, t_vec3 normal, t_color3 albedo);
t_square		*new_square(t_point3 point, t_vec3 normal \
							, float size, t_color3 albedo);

/*
** create and add object
*/

void			add_object(t_object **list, t_object *new);
t_object		*new_object(int type, void *element);

/*
** parsing
*/

void			parse_r(t_screen *screen, char **arr_split);
void			parse_c(t_screen *screen, char **arr_split);
void			parse_l(t_screen *screen, char **arr_split);
void			parse_a(t_screen *screen, char **arr_split);
void			parse_sp(t_screen *screen, char **arr_split);
void			parse_pl(t_screen *screen, char **arr_split);
void			parse_sq(t_screen *screen, char **arr_split);
void			parse_cy(t_screen *screen, char **arr_split);
void			parse_tr(t_screen *screen, char **arr_split);

/*
** ray
*/

t_ray			ray(t_point3 orig, t_vec3 dir);
t_point3		ray_at(t_ray *ray, double t);

/*
** validation
*/

int				validation_rgb(char *str);
int				validation_vec(char *str);
int				validation_point(char *str);
int				validation_cy(char **arr_split);
int				validation_sq(char **arr_split);
int				validation_pl(char **arr_split);
int				validation_r(char **str_arr);
int				validation_c(char **str_arr);
int				validation_a(char **str_arr);
int				validation_sp(char **str_arr);
int				validation_l(char **str_arr);
int				validation_tr(char **arr_split);

/*
** vector
*/

t_point3		v_plus(t_point3 v1, t_point3 v2);
t_point3		v_mul(double t, t_point3 v);
t_point3		v_mul2(t_point3 v1, t_point3 v2);
t_point3		v_minus(t_point3 v1, t_point3 v2);
t_point3		v_div(t_point3 v, double t);
double			v_len2(t_vec3 v);
double			v_len(t_vec3 v);
t_vec3			v_unit(t_vec3 v);
t_point3		vec(double x, double y, double z);
double			v_dot(t_vec3 v1, t_vec3 v2);
t_point3		point(double x, double y, double z);
t_color3		color(double x, double y, double z);
t_point3		v_min(t_vec3 v, t_vec3 l);
t_vec3			v_cross(t_vec3 v1, t_vec3 v2);
t_vec3			reflect(t_vec3 v, t_vec3 n);

/*
** bitmap
*/

void			save_bmp(t_screen *screen);

/*
** free
*/

void			free_all(t_screen *screen);
void			free_arr(char **str_arr);
void			free_obj(t_object *obj);

/*
** data_init
*/

void			data_init(t_screen *screen, char **arr_split, t_check *chk);

#endif
