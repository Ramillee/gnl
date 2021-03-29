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
