/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abang <abang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:38:41 by abang             #+#    #+#             */
/*   Updated: 2021/06/14 11:25:34 by abang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define END_OF_FILE 0
# define END_OF_LINE 1
# define ERROR -1

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef __STLIST__
#  define __STLIST__

typedef struct		s_list
{
	char			*content;
	int				status;
	struct s_list	*next;
}					t_list;

# endif

int					get_next_line(int fd, char **line);

void				ft_lst_set(t_list **lst, void *content, int status);
t_list				*ft_lst_new(void *content, int fd);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_lstlast(t_list *lst);
char				*ft_strcut(int i, int j, char *src);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strdup(const char *s1);

#endif
