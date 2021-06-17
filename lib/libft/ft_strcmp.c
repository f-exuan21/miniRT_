/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 19:39:47 by abang             #+#    #+#             */
/*   Updated: 2021/05/01 15:35:28 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(char *str1, char *str2)
{
	unsigned int	i;

	i = 0;
	while (str1[i] != 0 || str2[i] != 0)
	{
		if (str1[i] != str2[i])
			return ((int)str1[i] - (int)str2[i]);
		i++;
	}
	return (0);
}
