#include "get_next_line.h"

int			ft_len(char *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void		ft_del(char **tab)
{
	if (*tab != NULL)
	{
		free(*tab);
		*tab = NULL;
	}
}

void		ft_cpy(char *s1, char *s2, int n)
{
	while (n > 0)
	{
		*s1 = *s2;
		s1++;
		s2++;
		n--;
	}
}

char		*ft_strdup_gnl(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i])
		i++;
	if (!(dest = (char *)malloc(sizeof(*dest) * (i + 1))))
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
