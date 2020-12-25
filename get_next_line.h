/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atweek <atweek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:45:06 by atweek            #+#    #+#             */
/*   Updated: 2020/12/25 19:27:33 by atweek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

char	*gnl_strjoin(char *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*gnl_substr(char  *s, unsigned int start, size_t len, int flag);
int		get_next_line(int fd, char **line);

#endif
