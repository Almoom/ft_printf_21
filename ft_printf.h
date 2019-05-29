/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:28:59 by ljalikak          #+#    #+#             */
/*   Updated: 2019/04/29 13:29:01 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "/Users/ljalikak/Documents/Libft/Libft_21/libft.h"
# include <stdarg.h>

typedef struct		s_ld
{
	char			ld[129];
	int				pwr;
	char			num2[129];
	char			*num;
	char			mant2[129];
	char			*mant;
	int				len;
	int				acc;
}					t_ld;
char				*ft_strsum(char *s1, char *s2);
char				*ft_pwr2(int pwr);
int					ft_ldpwr(char *s);
void				ft_realpart(t_ld *list);
char				*ft_strdrop(char *s, int c, int n, int needfree);
void				ft_ldround(t_ld *list);
void				ft_ro(t_ld *list);
#endif
