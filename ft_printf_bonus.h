/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 21:33:26 by amanchon          #+#    #+#             */
/*   Updated: 2021/02/25 03:01:19 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct			s_param
{
	int					flag[5];
	int					width;
	int					pre;
	char				len[2];
	char				type;
	int					i;
}						t_param;

int						ft_findchr(char *s, char c);
char					*ft_strmcat(char *src, char *add);
char					*ft_ctostr(int size, char c);
//int						ft_strlen(const char *str);
char					*ft_strdup(const char *s);
char					**ft_split(char const *s, char c);
char					*ft_strmcatn(int n, char *s1, char *s2, ...);

char					*ft_putsign(t_param prm, char *ret, int neg,
int *nbchr);
char					*ft_putprecision(t_param prm, char *ret, int *nbchr);
char					*ft_putwiflag(t_param prm, char *ret, int *nbchr);
char					ft_findsign(t_param prm, int neg);
char					*ft_putflags(t_param prm, char *ret, int neg,
int *nbchr);

char					*ft_putdiezflag(t_param prm, char *ret, int *nbchr);
char					*ft_putprecision_fge(t_param prm, char *ret,
int *nbchr);
char					*ft_putflags_diux_fge(t_param prm, char *ret,
int neg, int *nbchr);

unsigned long long int	ft_atoull(char *str);
int						ft_atoi(const char *str);
char					*ft_itoa(int n);
char					*ft_itoa_base(long nbr, char *base);
int						ft_atoi_base(char *str, char *base);
char					*ft_ulltoa_base(unsigned long long nbr, char *base);

char					*ft_ftoa(double f);
char					*ft_ftoe(double f, int pre);
double					ft_atof(char *str);

t_param					ft_initparam(char *str, int i);
t_param					ft_getparam(char *str, int i, va_list vl);
char					*ft_retarg(va_list vl, t_param prm);
char					*ft_putparam(va_list vl, t_param prm, int *nbchr);
char					*ft_param_spe(t_param prm, char *tmp, int *nbchr);
int						ft_printf(const char *str, ...);

char					*ft_arrondi_str(int pre, char *str);
char					*ft_printg(double f, t_param prm);

#endif
