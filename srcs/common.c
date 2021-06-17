/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 18:37:00 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:04:28 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/*
** 두 벡터의 내적 값이 음수 일 때 두 벡터가 반대 방향임을 알 수 있음.
** 두 벡터가 같은 방향일 경우 반대 방향으로 바꿔준다. -> default로 생각하기 위해
*/

void			set_face_normal(t_ray *r, t_rec *rec)
{
	rec->front_face = v_dot(r->dir, rec->n) < 0;
	rec->n = rec->front_face ? rec->n : v_mul(-1, rec->n);
}

/*
** o < x < max 인 난수를 생성한다.
*/

float			random_float(float max)
{
	return (rand() / (RAND_MAX + 1.0) * max);
}

/*
** -1 < x < 1 인 난수를 생성한다.
*/

float			random_float_2(void)
{
	float		min;
	float		max;

	min = -1.0;
	max = 1.0;
	return (min + (max - min) * random_float(max));
}

float			degrees_to_radians(float degree)
{
	float	radian;

	radian = degree * PI / 180;
	return (radian);
}

int				arr_len(char **str_arr)
{
	int		len;

	len = 0;
	while (str_arr[len] != NULL)
		len++;
	return (len);
}
