/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_cmm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:02:31 by abang             #+#    #+#             */
/*   Updated: 2021/06/17 02:54:36 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int			validation_point(char *str)
{
	char	**tmp;
	int		len;

	len = 0;
	tmp = ft_split(str, ',');
	while (tmp[len] != NULL)
	{
		if (!ft_isfloat(tmp[len]))
			return (0);
		len++;
	}
	free_arr(tmp);
	if (len != 3)
		return (0);
	return (1);
}

int			validation_vec(char *str)
{
	char	**tmp;
	int		len;
	float	ftmp;

	len = 0;
	tmp = ft_split(str, ',');
	while (tmp[len] != NULL)
	{
		if (!ft_isfloat(tmp[len]))
			return (0);
		len++;
	}
	if (((ftmp = ft_atof(tmp[0])) < -1 || ftmp > 1) \
		|| ((ftmp = ft_atof(tmp[1])) < -1 || ftmp > 1) \
		|| ((ftmp = ft_atof(tmp[2])) < -1 || ftmp > 1))
		return (0);
	free_arr(tmp);
	if (len != 3)
		return (0);
	return (1);
}

int			validation_rgb(char *str)
{
	char	**tmp;
	int		len;
	int		i;

	len = 0;
	tmp = ft_split(str, ',');
	while (tmp[len] != NULL)
	{
		i = 0;
		while (tmp[len][i] != '\0')
		{
			if (!ft_isdigit(*tmp[len]))
				return (0);
			i++;
		}
		if (ft_atoi(tmp[len]) > 255)
			return (0);
		len++;
	}
	free_arr(tmp);
	if (len != 3)
		return (0);
	return (1);
}
