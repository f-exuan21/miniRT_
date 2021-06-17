/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 15:43:29 by abang             #+#    #+#             */
/*   Updated: 2021/06/13 16:04:26 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float			clamp(float x)
{
	if (x < 0.0)
		return (0.0);
	if (x > 0.999)
		return (0.999);
	return (x);
}

void			error(char *str)
{
	write(1, "Error\n", 6);
	perror(str);
	exit(1);
}
