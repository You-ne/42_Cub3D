/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 15:42:07 by amanchon          #+#    #+#             */
/*   Updated: 2020/01/16 15:32:57 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_find_sep(char c, char charset)
{
	if (c == charset)
		return (1);
	if (c == '\0')
		return (1);
	return (0);
}

int			ft_count_numb_of_word(char *str, char c)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((ft_find_sep(str[i + 1], c) == 1 &&
					ft_find_sep(str[i], c) == 0))
			words++;
		i++;
	}
	return (words);
}

void		ft_copy_word(char *dest, char *from, char c)
{
	int		i;

	i = 0;
	while (ft_find_sep(from[i], c) == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

void		ft_transfert_to_tab(char **tab, char *str, char c)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_find_sep(str[i], c) == 1)
			i++;
		else
		{
			j = 0;
			while (ft_find_sep(str[i + j], c) == 0)
				j++;
			tab[word] = (char*)malloc(sizeof(char) * (j + 1));
			ft_copy_word(tab[word], str + i, c);
			i = i + j;
			word++;
		}
	}
}

char		**ft_split(char const *s, char c)
{
	char	**tab;
	int		word;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	word = ft_count_numb_of_word(str, c);
	if ((tab = (char**)malloc(sizeof(char*) * (word + 1))) == NULL)
		return (NULL);
	tab[word] = 0;
	ft_transfert_to_tab(tab, str, c);
	return (tab);
}
