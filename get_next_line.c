/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarazak <mnarazak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 16:41:57 by mnarazak          #+#    #+#             */
/*   Updated: 2020/08/18 23:44:13 by mnarazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	str_free(char **str)
{
	free(*str);
	*str = NULL;
}

static int	make_line(char **s, char **line)
{
	int		len;
	char	*tmp;

	len = 0;
	while ((*s)[len] != '\n' && (*s)[len] != '\0')
		len++;
	if ((*s)[len] == '\n')
	{
		*line = ft_substr(*s, 0, len);
		if (!(tmp = ft_strdup(&((*s)[len + 1]))))
			return (ERROR);
		free(*s);
		*s = tmp;
		if ((*s)[0] == '\0')
			str_free(s);
		return (SUCCESS);
	}
	else
	{
		if (!(*line = ft_strdup(*s)))
			return (ERROR);
		str_free(s);
		return (EOF_REACHED);
	}
}

static int	output(char **s, char **line, int ret, int fd)
{
	if (ret < 0)
		return (ERROR);
	else if (ret == 0 && s[fd] == NULL)
	{
		if (!((*line) = ft_strdup("\0")))
			return (ERROR);
		return (EOF_REACHED);
	}
	else
		return (make_line(&s[fd], line));
}

static int	get_next_line_main(char **s, char **line, int fd, char *buff)
{
	char	*tmp;
	ssize_t	ret;

	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (s[fd] == NULL)
		{
			if (!(s[fd] = ft_strdup(buff)))
				return (ERROR);
		}
		else
		{
			if (!(tmp = ft_strjoin(s[fd], buff)))
				return (ERROR);
			free(s[fd]);
			s[fd] = tmp;
		}
		if (ft_strchr(s[fd], '\n'))
			break ;
	}
	free(buff);
	buff = NULL;
	return (output(s, line, ret, fd));
}

int			get_next_line(const int fd, char **line)
{
	static char	*s[FOPEN_MAX];
	char		*buff;

	if (fd < 0 || FOPEN_MAX <= fd || BUFFER_SIZE <= 0)
		return (ERROR);
	if (!(buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (ERROR);
	return (get_next_line_main(s, line, fd, buff));
}
