/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:32:45 by yotillar          #+#    #+#             */
/*   Updated: 2020/10/13 20:16:57 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join(char *tab, char *buf)
{
	int			i;
	int			j;
	char		*ptr;

	i = 0;
	j = 0;
	if (tab != NULL)
		i = ft_len(tab);
	j = ft_len(buf);
	if (!(ptr = (char*)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	ft_cpy(ptr, tab, i);
	ft_cpy(ptr + i, buf, j);
	ptr[i + j] = '\0';
	ft_del(&tab);
	return (ptr);
}

int		ft_end(char *tab)
{
	int			count;

	count = 0;
	while (tab[count] && tab[count] != '\n')
		count++;
	if (tab[count] == '\n')
	{
		tab[count] = '\0';
		return (count);
	}
	return (-1);
}

int		ft_test(char **tab, char *buf, char **line)
{
	char		*tmp;
	int			final;

	final = -1;
	*tab = ft_join(*tab, buf);
	if (*tab != NULL)
		final = ft_end(*tab);
	if (final > -1)
	{
		*line = ft_strdup_gnl(*tab);
		tmp = *tab;
		*tab = ft_strdup_gnl((*tab + final + 1));
		ft_del(&tmp);
		return (1);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int				res;
	char			b[BUFFER_SIZE + 1];
	static char		*tab[1000];

	if (BUFFER_SIZE < 1 || fd < 0 || !line || (res = read(fd, b, 0)) < 0)
		return (-1);
	while ((res = read(fd, b, BUFFER_SIZE)) > 0)
	{
		b[res] = '\0';
		res = ft_test(&tab[fd], b, line);
		if (res == 1)
			return (1);
	}
	b[res] = '\0';
	if ((res = ft_test(&tab[fd], b, line)) == 1)
		return (1);
	else if (tab[fd] != NULL && ft_len(tab[fd]) > 0)
	{
		*line = ft_strdup_gnl(tab[fd]);
		ft_del(&tab[fd]);
	}
	ft_del(&tab[fd]);
	return (0);
}
