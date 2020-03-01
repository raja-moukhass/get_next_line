/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 05:13:49 by ramoukha          #+#    #+#             */
/*   Updated: 2019/06/26 21:26:03 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_store(char **tmp, char **line)
{
	int		i;
	char	*left;
	char	*tmp1;

	i = 0;
	tmp1 = *tmp;
	while (tmp1[i] != '\n' && tmp1[i] != '\0')
		i++;
	*line = ft_strsub(tmp1, 0, i);
	if (tmp1[i] == '\0')
	{
		ft_strdel(tmp);
		return (NULL);
	}
	left = ft_strdup(&tmp1[i] + 1);
	ft_strdel(tmp);
	return (left);
}

int		get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	int			rd;
	static char	*left[4865];
	char		*tmp;

	if (fd < 0 || line == NULL || fd > 4864)
		return (-1);
	if (left[fd] == NULL)
		left[fd] = ft_strnew(0);
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[rd] = '\0';
		tmp = left[fd];
		left[fd] = ft_strjoin(left[fd], buf);
		ft_strdel(&tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (rd == -1)
		return (-1);
	left[fd] = ft_store(&left[fd], line);
	if (**line == '\0' && left[fd] == NULL && rd == 0)
		ft_strdel(line);
	return (!(!*line && left[fd] == NULL && rd == 0));
}
