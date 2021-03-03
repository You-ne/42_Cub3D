/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:07:41 by yotillar          #+#    #+#             */
/*   Updated: 2020/10/13 20:17:23 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int			get_next_line(int fd, char **line);
int			ft_len(char *s);
void		ft_del(char **tab);
void		ft_cpy(char *s1, char *s2, int n);
char		*ft_strdup_gnl(char *src);
#endif
