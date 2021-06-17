/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:36:50 by abang             #+#    #+#             */
/*   Updated: 2020/12/27 12:52:45 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	num;

	if (n < 0)
	{
		num = (-1) * (long long)n;
		ft_putchar_fd('-', fd);
	}
	else
		num = n;
	if (num > 9)
		ft_putnbr_fd(num / 10, fd);
	ft_putchar_fd('0' + (num % 10), fd);
}
