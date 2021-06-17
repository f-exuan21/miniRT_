/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 13:35:19 by abang             #+#    #+#             */
/*   Updated: 2021/06/17 03:06:55 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			free_obj(t_object *obj)
{
	t_object	*tmp;
	t_object	*tmp2;

	tmp = obj;
	while (tmp)
	{
		free(tmp->element);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

void			free_all(t_screen *screen)
{
	free_obj(screen->object);
	free_obj(screen->camera);
	free_obj(screen->light);
}

void			free_arr(char **str_arr)
{
	int		i;

	i = 0;
	while (str_arr[i])
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr[i]);
	free(str_arr);
}
