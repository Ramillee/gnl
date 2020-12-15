/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atweek <atweek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:44:39 by atweek            #+#    #+#             */
/*   Updated: 2020/12/15 16:50:01 by atweek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 3

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
	int		i;
	char	*str_temp;
	
	i = 0;
	index = 0;
	// p_str = *str;
	if (!(*str = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
	{
		// free(*str);
		return (-1);
	}
	// p_str[0] = '\0';
	if (!(str_temp = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
	{
		free(*str);
		return (-1);
	}
	// str_temp = str_temp + ft_strlen(str_temp);
	while ((rs = read(fd, str_temp, BUFFER_SIZE)) > 0)
	{
		str_temp[rs] = '\0';
		*str = ft_strjoin(*str,str_temp);
		if ((index = find_n(*str)) > 0)
			break ;
	}
	if ((rs == -1) || (rs == 0))
		return (rs);//free
	*line = ft_substr(*str,0,index - 1);
	*str = ft_substr(*str,index,ft_strlen(*str));
	free(str_temp);
	str_temp = NULL;
	return (rs);	
}

int		get_next_line(int fd, char **line)
{
	int				flag;
	static char		*static_str;
	int				index;
	
	index = 0;
	if (static_str)
	{
		if ((index = find_n(static_str)) > 0)
		{
			*line = ft_substr(static_str,0, index - 1);
			static_str = ft_substr(static_str, index, ft_strlen(static_str));
		}
		else
		{
			if ((flag = read_buf(fd,&static_str,line)) == -1)
				return (-1); //free
			if ((flag = read_buf(fd,&static_str,line)) == 0)
			{
				*line = ft_substr(static_str,0,ft_strlen(static_str));
				return (0);
			}
		}
		
	}
	else
	{
		if ((flag = read_buf(fd,&static_str,line)) == -1)
			return (-1); //free
	}
	return(1);
}

int main(void)
{
	int fd;
	char *line;
	int i;

	i = 0;
	fd = open("text",O_RDONLY);
	while (get_next_line(fd, &line))
	{
		printf("%s\n", line);
		// free(line);
	}
	printf("%s\n", line);
	// free(line);
	return (0);
} 