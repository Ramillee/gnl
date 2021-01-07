/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atweek <atweek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:35:02 by atweek            #+#    #+#             */
/*   Updated: 2021/01/06 17:54:28 by atweek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	clean_before_out(char *s1, char *s2, int ret)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (ret);
}

static int	find_n(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (-1);
	else
		return (i + 1);
}

static int	read_buf(int fd, char **str, char **line)
{
	int		rs;
	int		index;
	char	*str_read;

	index = 0;
	if (!*str)
	{
		*str = malloc(1);
		*str[0] = '\0';
	}
	if (!(str_read = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (clean_before_out(*str, str_read, -1));
	while ((rs = read(fd, str_read, BUFFER_SIZE)) > 0)
	{
		str_read[rs] = '\0';
		*str = gnl_strjoin(*str, str_read);
		if ((index = find_n(*str)) > 0)
			break ;
	}
	if ((rs == -1) || (rs == 0))
		return (clean_before_out(NULL, str_read, rs));
	*line = gnl_substr(*str, 0, index - 1, 0);
	*str = gnl_substr(*str, index, ft_strlen(*str) - ft_strlen(*line), 1);
	return (clean_before_out(str_read, NULL, rs));
}

static int	cut_end(char **line, char **static_str, int flag)
{
	int index;

	if (flag == -1)
		return (clean_before_out(*static_str, NULL, -1));
	while (*static_str)
	{
		*line = gnl_substr(*static_str, 0,
						(index = find_n(*static_str)) - 1, 0);
		*static_str = gnl_substr(*static_str, index + 1,
						ft_strlen(*static_str), 1);
		if (index == -1)
		{
			free(*static_str);
			*static_str = NULL;
			return (0);
		}
		return (1);
	}
	return (clean_before_out(*static_str, NULL, 0));
}

int			get_next_line(int fd, char **line)
{
	int				flag;
	static char		*static_str;
	int				index;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	index = 0;
	if (static_str)
	{
		if ((index = find_n(static_str)) > 0)
		{
			*line = gnl_substr(static_str, 0, index - 1, 0);
			static_str = gnl_substr(static_str, index,
						ft_strlen(static_str), 1);
		}
		else if ((flag = read_buf(fd, &static_str, line)) == -1 || (flag == 0))
			return (cut_end(line, &static_str, flag));
	}
	else if (((flag = read_buf(fd, &static_str, line)) == -1) || (flag == 0))
		return (cut_end(line, &static_str, flag));
	return (1);
}
