/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 15:37:18 by abang             #+#    #+#             */
/*   Updated: 2021/06/17 03:07:59 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void			bmp_body(t_screen *screen, int fd)
{
	int				i;
	int				j;
	unsigned int	color;

	j = screen->height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < screen->width)
		{
			color = *(unsigned int *)(screen->addr + \
					(j * screen->size_l + i * (screen->bpp / 8)));
			if (write(fd, &color, screen->bpp / 8) == -1)
			{
				close(fd);
				error("Failed to write img.");
			}
			i++;
		}
		j--;
	}
}

void			set_int_to_char(unsigned char *data, int val)
{
	data[0] = (unsigned char)(val);
	data[1] = (unsigned char)(val >> 8);
	data[2] = (unsigned char)(val >> 16);
	data[3] = (unsigned char)(val >> 24);
}

void			bmp_header(int file_size, int fd, t_screen *screen)
{
	unsigned char	data[54];
	int				i;

	i = 0;
	while (i < 54)
		data[i++] = (unsigned char)(0);
	data[0] = (unsigned char)('B');
	data[1] = (unsigned char)('M');
	set_int_to_char(data + 2, file_size);
	data[10] = (unsigned char)(54);
	data[14] = (unsigned char)(40);
	set_int_to_char(data + 18, screen->width);
	set_int_to_char(data + 22, screen->height);
	data[26] = (unsigned char)(1);
	data[28] = (unsigned char)(screen->bpp);
	set_int_to_char(data + 38, 5000);
	set_int_to_char(data + 42, 5000);
	if (write(fd, data, 54) == -1)
	{
		close(fd);
		error("Failed to create bmp file header.");
	}
}

char			*file_name(int num)
{
	char		*name[3];
	char		*rst;
	char		*tmp;

	name[0] = "screenshot";
	name[1] = ft_itoa(num);
	name[2] = ".bmp";
	tmp = ft_strjoin(name[0], name[1]);
	rst = ft_strjoin(tmp, name[2]);
	free(tmp);
	free(name[1]);
	return (rst);
}

/*
** 0 ~ 53 비트 까지는 비트맵의 헤더이다.
** 54부터 이미지의 데이터가 들어간다.
** 비트맵은 bottom->up이 default이다. => 거꾸로 저장해야함.
*/

void			save_bmp(t_screen *screen)
{
	int			file_size;
	int			fd;
	t_object	*img;
	char		*name;
	int			num;

	num = 0;
	file_size = 54 + (screen->width * screen->height) * 4;
	img = screen->img_list;
	while (img)
	{
		screen->addr = ((t_img *)img->element)->addr;
		screen->img = ((t_img *)img->element)->img;
		name = file_name(num);
		fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (fd == -1)
			error("Failed to create bmp file.");
		bmp_header(file_size, fd, screen);
		bmp_body(screen, fd);
		close(fd);
		img = img->next;
		num++;
		free(name);
	}
	exit(1);
}
