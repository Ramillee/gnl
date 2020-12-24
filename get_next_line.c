/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atweek <atweek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:44:39 by atweek            #+#    #+#             */
/*   Updated: 2020/12/24 21:14:09 by atweek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #define BUFFER_SIZE 32

int		find_n(char *str)
{
	int	i;

	if (!str)
		return (-1);
	
	i = 0;
	while(str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (-1);
	else
		return (i + 1);
	
}

int		read_buf(int fd, char **str, char **line)
{
	int		rs;
	int		index;
	// int		i;
	char	*str_read;

	// i = 0;
	index = 0;
	if (!*str)
	{
		*str = malloc(1);
		*str[0] = '\0';
	}
	if (!(str_read = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
	{
		free(*str);
		return (-1);
	}
	while ((rs = read(fd, str_read, BUFFER_SIZE)) > 0)
	{
		str_read[rs] = '\0';
		*str = ft_strjoin(*str,str_read);
		if ((index = find_n(*str)) > 0)
			break ;
	}
	if ((rs == -1) || (rs == 0))
		return (rs);//free
	*line = ft_substr(*str,0,index - 1,0);
	*str = ft_substr(*str,index,ft_strlen(*str) - ft_strlen(*line),1);
	free(str_read);
	str_read = NULL;
	return (rs);	
}

int		cut_end(char **line, char **static_str, int flag)
{
	int index;
	
	if (flag == -1)
		return (-1);//free
	while (*static_str)
	{
		*line = ft_substr(*static_str,0,(index = find_n(*static_str)) - 1,0);
		*static_str = ft_substr(*static_str,index + 1,ft_strlen(*static_str),1);
		if (index == -1)
		{
			free(*static_str);
			*static_str = NULL;
			return (0);
		}
		return (1);
	}
	free(*static_str);
	*static_str = NULL;
	return (0);
}
int		get_next_line(int fd, char **line)
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
			*line = ft_substr(static_str,0, index - 1,0);
			static_str = ft_substr(static_str, index, ft_strlen(static_str),1);
		}
		else
			if ((flag = read_buf(fd,&static_str,line)) == -1 || (flag == 0))
				return(cut_end(line, &static_str, flag));
	}
	else
		if (((flag = read_buf(fd,&static_str,line)) == -1) || (flag == 0))
		{
			return(cut_end(line, &static_str, flag));
		}
	return(1);
}

// int main(void)
// {
// 	int fd;
// 	char *line;
// 	// int i;
// 	int	gnl;

// 	// gnl = 0;
// 	// i = 0;
// 	fd = open("text",O_RDONLY);//alphabet
// 	// fd = 700;
	
// 	while ((gnl = get_next_line(fd,&line)) > 0)
// 	{
// 		printf("%d -- %s\n",gnl,line);
// 		free(line);
// 		// i ++;
// 		// printf("%d -- %s строка %d\n",gnl,line,i);
// 		// ft_putstr_fd(line,1);
// 		// ft_putchar_fd(10,1);
// 		// i++;
		
// 		//free(line);
// 		//line = NULL;
// 	}
// 	// printf("%s\n", line);
// 	printf("%d -- %s",gnl,line);
// 	// free(line);
// 	// printf("%d -- %s строка %d\n",gnl,line,i);
// 	// ft_putstr_fd(line,1);
// 	free(line);
// 	sleep(5);
// 	return (0);
// } 