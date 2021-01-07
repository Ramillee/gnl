/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atweek <atweek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:45:06 by atweek            #+#    #+#             */
/*   Updated: 2021/01/06 17:54:37 by atweek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

char	*gnl_strjoin(char *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*gnl_substr(char *s, unsigned int start, size_t len, int flag);
int		get_next_line(int fd, char **line);

#endif
