/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 15:44:01 by abang             #+#    #+#             */
/*   Updated: 2021/06/17 14:54:18 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void		screen_init(t_screen *screen)
{
	screen->object = NULL;
	screen->light = NULL;
	screen->camera = NULL;
	screen->img_list = NULL;
}

void		check_at_least(t_check chk)
{
	if (chk.r == 0 || chk.c == 0 || chk.a == 0)
		error("R, A and c need be declared at least once.");
	else if (chk.r > 1 || chk.a > 1)
		error("R and A must be declared only once.");
}

void		organized_line(t_screen *screen, t_check *chk, char **line)
{
	char		**arr_split;

	arr_split = ft_splitstr(*line, " \t\v\f\r");
	if (arr_split != NULL)
	{
		data_init(screen, arr_split, chk);
		free_arr(arr_split);
	}
}

void		read_file(t_screen *screen, char *file_name)
{
	int			fd;
	char		**line;
	int			rst;
	t_check		chk;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		error("file open failed");
	screen_init(screen);
	line = (char **)malloc(sizeof(char *));
	chk = (t_check){0, 0, 0};
	while ((rst = get_next_line(fd, line)) > 0)
	{
		organized_line(screen, &chk, line);
		free(*line);
	}
	organized_line(screen, &chk, line);
	free(*line);
	free(line);
	check_at_least(chk);
}
