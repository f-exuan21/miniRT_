/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:52:24 by abang             #+#    #+#             */
/*   Updated: 2021/06/17 03:07:56 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int				key_hook(int key, t_screen *screen)
{
	t_img		*img;

	if (key == ESC)
	{
		mlx_destroy_window(screen->mlx, screen->win);
		exit(1);
	}
	else if (key == N)
	{
		if (screen->current_img->next != NULL)
			screen->current_img = screen->current_img->next;
		else
			screen->current_img = screen->img_list;
		img = screen->current_img->element;
		mlx_put_image_to_window(screen->mlx, screen->win, img->img, 0, 0);
	}
	return (0);
}

int				exit_hook(t_screen *screen)
{
	mlx_destroy_window(screen->mlx, screen->win);
	exit(1);
}

void			show_img(t_screen *screen)
{
	free_all(screen);
	mlx_put_image_to_window(screen->mlx, screen->win,\
							((t_img *)screen->current_img->element)->img, 0, 0);
	mlx_hook(screen->win, 2, 0, key_hook, screen);
	mlx_hook(screen->win, 17, 0, exit_hook, screen);
	mlx_loop(screen->mlx);
}

int				main(int argc, char **argv)
{
	t_screen	screen;
	char		**params;

	if (argc == 2 || argc == 3)
	{
		params = ft_split(argv[1], '.');
		if (arr_len(params) != 2 || ft_strcmp(params[1], "rt"))
			error("Invalid File.");
		free_arr(params);
		if (argc == 3 && ft_strcmp(argv[2], "--save") != 0)
			error("Invalid Parameter.");
		read_file(&screen, argv[1]);
		screen.mlx = mlx_init();
		screen.win = mlx_new_window(
					screen.mlx, screen.width, screen.height, "test");
		setting_img(&screen);
		if (argc == 3)
			save_bmp(&screen);
		show_img(&screen);
	}
	else
		error("Invalid Parameter.");
	return (0);
}
