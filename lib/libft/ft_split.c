/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 12:42:26 by abang             #+#    #+#             */
/*   Updated: 2021/05/02 15:28:02 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_splitnum(char const *s, char c)
{
	int		i;
	int		cnt;

	if (!s[0])
		return (0);
	i = 0;
	cnt = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			cnt++;
			while (s[i] == c && s[i])
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		cnt++;
	return (cnt);
}

int		ft_split_str_len(char **s, char c)
{
	unsigned int	len;

	len = 0;
	while (**s && **s == c)
		(*s)++;
	while (**s && **s != c)
	{
		len++;
		(*s)++;
	}
	return (len);
}

char	**ft_free(char **str, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		free(str[j]);
		j++;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**str_arr;
	char	*tmp;
	int		cnt;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	cnt = ft_splitnum(s, c);
	if (!(str_arr = malloc(sizeof(char *) * (cnt + 1))))
		return (NULL);
	i = 0;
	tmp = (char *)s;
	while (cnt-- > 0)
	{
		while (*tmp && *tmp == c)
			tmp++;
		if (*tmp && *tmp != c)
			len = ft_split_str_len(&tmp, c);
		if (!(str_arr[i] = malloc(sizeof(char) * (len + 1))))
			return (ft_free(str_arr, i));
		ft_strlcpy(str_arr[i++], tmp - len, len + 1);
	}
	str_arr[i] = NULL;
	return (str_arr);
}
