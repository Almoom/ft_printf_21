/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:39:50 by ljalikak          #+#    #+#             */
/*   Updated: 2019/04/29 13:39:52 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_arrrev(char *s)
{
	char	c;
	size_t	i;
	size_t	k;

	if (!s)
		return ;
	k = -1;
	i = ft_strlen(s);
	while (++k < i / 2)
	{
		c = s[k];
		s[k] = s[i - k - 1];
		s[i - k - 1] = c;
	}
}

char	*ft_strnzero(char *s, size_t n)
{
	size_t	i;
	int		len;

	i = -1;
	len = ft_strlen(s);
	while (++i < n - len)
		s = ft_strjoinchar(s, '0', 1);
	return (s);
}

size_t	ft_max(char **s1, char **s2)
{
	size_t max;

	max = (ft_strlen(*s1) > ft_strlen(*s2)) ? ft_strlen(*s1) : ft_strlen(*s2);
	if (ft_strlen(*s1) - ft_strlen(*s2) != 0)
	{
		*s1 = ft_strnzero(*s1, max);
		*s2 = ft_strnzero(*s2, max);
	}
	return (max);
}

char	*ft_strsum(char *s1, char *s2)
{
	int		i;
	char	*sum;
	size_t	max;

	max = ft_max(&s1, &s2);
	sum = ft_memset(ft_strnew(max + 1), '0', max + 1);
	i = -1;
	while (s1[++i])
	{
		if (s1[i] + s2[i] + sum[i] - 3 * '0' < 10)
			sum[i] = (s1[i] - '0') + (s2[i] - '0') + sum[i];
		else
		{
			sum[i + 1] = '1';
			sum[i] = (s1[i] + s2[i] + sum[i] - 3 * '0') % 10 + '0';
		}
	}
	if (s1 == s2)
		free(s1);
	else
	{
		free(s1);
		free(s2);
	}
	return (sum);
}

char	*ft_pwr2(int pwr)
{
	char *t;

	t = ft_strdup("1");
	while (pwr-- > 0)
		t = ft_strsum(t, t);
	t = ft_strrev(t, 1);
	return (t);
}

int		ft_ldpwr(char *s)
{
	int		pwr;
	size_t	i;
	char	*t;

	i = 16;
	pwr = 1;
	while (--i > 1)
	{
		t = ft_pwr2(15 - i);
		if (s[1] == '1')
			pwr = (s[i] == '1') ? pwr + ft_atoi(t) : pwr;
		else
			pwr = (s[i] == '0') ? pwr + ft_atoi(t) : pwr;
		free(t);
	}
	pwr = (s[1] == '1') ? pwr : 1 - pwr;
	return (pwr);
}

void	ft_ldarrnew(char *s, int start, int n, char *new)
{
	int i;
	int tmp;

	i = 0;
	tmp = start;
	while (start < n + tmp)
		new[i++] = s[start++];
}

char	*ft_ldaccuracy(char *s, int t, int len)
{
	char *tmp;

	t = (len + t + 1 > (int)ft_strlen(s) - 1) ? ft_strlen(s) - 1 : t;
	tmp = ft_strsub(s, 1, ((int)ft_strlen(s) > len + t) ? len + t + 1 :
	ft_strlen(s) - 1);
	free(s);
	return (tmp);
}

void	ft_strdvd(t_ld *list)
{
	char	*rez;
	char	*m;
	int		k;
	int		i;

	i = list->pwr < 0 ?
	ft_strlen(list->mant2) - 1 + -list->pwr : 64 - ft_strlen(list->num2);
	while (i-- > 0)
	{
		m = ft_strdup("0");
		rez = ft_strnew(0);
		k = -1;
		while (list->mant[++k])
		{
			rez = ft_strjoinchar(rez, (list->mant[k] - '0') / 2 + '0', 1);
			m = ft_strjoinchar(m, (list->mant[k] - 48) % 2 == 0 ? '0' : '5', 1);
			if (!(list->mant)[k + 1] && (list->mant[k] - '0') % 2 == 1)
				rez = ft_strjoinchar(rez, '0', 1);
		}
		m[ft_strlen(m) - 1] = m[ft_strlen(m) - 1] == 48 ?
		0 : m[ft_strlen(m) - 1];
		rez = ft_strrev(ft_strsum(ft_strrev(rez, 1), ft_strrev(m, 1)), 1);
		free(list->mant);
		list->mant = ft_ldaccuracy(rez, list->acc + 32, list->len);
	}
}

void	ft_unrealpart(t_ld *list)
{
	int	i;
	int	len;

	i = -1;
	list->mant = ft_strdup("0");
	ft_arrrev(list->mant2);

	while (list->mant2[++i])
		list->mant = ft_strrev(ft_strsum(ft_strrev(list->mant, 1),
		ft_strrev((list->mant2[i] == '1') ?
		ft_pwr2(i) : ft_strdup("0"), 1)), 1);
	//list->mant = ft_strdrop(list->mant, '0', 0, 1);
	len = ft_strlen(list->mant2);
	// while (--len > -1 && list->mant2[len] == '0')
	// 	list->mant2[len] = 0;
	list->len = ((int)ft_strlen(list->mant) > list->pwr) ?
	(int)ft_strlen(list->mant) : list->pwr;
	ft_strdvd(list);
	printf("==%zu %s\n", ft_strlen(list->num2), list->num2);
	printf("==%zu %s\n", ft_strlen(list->mant2), list->mant2);
	// list->len = ft_strlen(list->num2) - ft_strlen(list->mant2) > 5 ? list->len - 2 : list->len;
	// list->len = ft_strlen(list->num2) - ft_strlen(list->mant2) > 13 ? list->len - 6 : list->len;
	// list->len = ft_strlen(list->num2) - ft_strlen(list->mant2) > 24 ? list->len - 6 : list->len;
	// list->len = ft_strlen(list->num2) - ft_strlen(list->mant2) > 31 ? list->len - 8 : list->len;
	printf("==%lu\n", ft_strlen(list->num2) - ft_strlen(list->mant2));
	list->mant = ft_strdrop(list->mant, '0', list->len, 1);
	while ((int)ft_strlen(list->mant) < list->acc)
		list->mant = ft_strjoinchar(list->mant, '0', 1);
	printf("==%d\n", list->len);
	ft_ro(list);
}

void	ft_odin(t_ld *list)
{
	char *t;

	t = NULL;
	if ((int)ft_strlen(list->mant) > list->acc)
	{
		list->num = ft_strrev(ft_strsum(ft_strrev(list->num, 1),
		ft_strdup("1")), 1);
		list->num = ft_strdrop(list->num, '0', 0, 1);
		t = ft_strsub(list->mant, 1, ft_strlen(list->mant) - 1);
		free(list->mant);
		list->mant = ft_strdup(t);
	}
	free(t);
}

void	ft_ldround2(t_ld *list, char c2, char *t1, char *t2)
{
	free(list->mant);
	t1 = ft_strrev(t1, 1);

	if (c2 == '9')
	{
		list->mant = ft_strrev(ft_strsum(t1, ft_strdup("1")), 1);
		list->mant = ft_strdrop(list->mant, '0', 1, 1);
		free(t2);
		ft_odin(list);
	}
	else
	{
		list->mant = ft_strjoinchar(t2, c2 + 1, 1);
		free(t1);
	}
}

void	ft_ldround(t_ld *list)
{
	char	c2;
	char	*t1;
	char	*t2;

	c2 = list->mant[ft_strlen(list->mant) - 2];
	t1 = ft_strsub(list->mant, 0, ft_strlen(list->mant) - 1);
	t2 = ft_strsub(list->mant, 0, ft_strlen(list->mant) - 2);
	if (list->mant[ft_strlen(list->mant) - 1] > '4')
		ft_ldround2(list, c2, t1, t2);
	else if (list->mant[ft_strlen(list->mant) - 1] == '0')
	{
		if ((int)ft_strlen(list->mant) > list->acc)
		{
			free(list->mant);
			list->mant = ft_strdup(t1);
		}
		free(t1);
		free(t2);
	}
	else
	{
		free(list->mant);
		list->mant = ft_strjoinchar(t2, c2, 1);
		free(t1);
	}
}

int		ft_strnotchr(char *s, int n)
{
	int i;

	i = 0;
	while (s[i + n])
	{
		if (s[i + n] != '0')
			return (1);
		i++;
	}
	return (0);
}

void	ft_ro(t_ld *list)
{
	char *tmp;

	tmp = NULL;
	if (list->mant[list->acc] == '5' && !ft_strnotchr(list->mant, list->acc + 1)
	&& (list->mant[list->acc - 1] - '0') % 2 == 0)
	{
		tmp = ft_strsub(list->mant, 0, list->acc - 1);
		free(list->mant);
		list->mant = ft_strdup(tmp);
		ft_ldround(list);
	}
	else
	{
		tmp = ft_strsub(list->mant, 0, list->acc + 1);
		free(list->mant);
		list->mant = ft_strdup(tmp);
		ft_ldround(list);
	}
	free(tmp);
}

void	ft_ldseparat(t_ld *list)
{
	int		k;

	k = list->pwr > 64 ? 64 : list->pwr + 1;
	if (list->pwr == 16384 && ft_strchr(list->ld + 17, '1') != NULL)
		list->num = ft_strdup("nan");
	else if (list->pwr == 16384 && ft_strchr(list->ld + 17, '1') == NULL)
		list->num = (list->ld[0] == '0') ? ft_strdup("inf") : ft_strdup("-inf");
	else if (list->pwr >= 0)
	{
		ft_ldarrnew(list->ld, 16, k, list->num2);
		ft_ldarrnew(list->ld, k + 16, 64, list->mant2);
		ft_realpart(list);
		ft_unrealpart(list);
	}
	else
	{
		list->num = (list->ld[0] == '0') ? ft_strdup("0") : ft_strdup("-0");
		ft_ldarrnew(list->ld, 16, 64, list->mant2);
		ft_unrealpart(list);
	}
}

void	ft_ldbit(char *s, void *v, int size)
{
	int		t;
	int		i;
	int		j;

	j = 0;
	size = size > 10 ? 10 : size;
	while (size-- > 0)
	{
		t = *((unsigned char *)v + size);
		i = 7;
		while (i > -1)
		{
			s[i-- + j * 8] = t % 2 + '0';
			t /= 2;
		}
		j++;
	}
}

t_ld	*ft_lstcrt(long double d)
{
	t_ld *list;

	if (!(list = (t_ld *)ft_memalloc(sizeof(t_ld))))
		return (NULL);
	ft_ldbit(list->ld, &d, sizeof(d));
	list->pwr = ft_ldpwr(list->ld);
	list->num = NULL;
	list->mant = NULL;
	list->len = 0;
	list->acc = 7;
	ft_ldseparat(list);
	return (list);
}

char	*ft_strdrop(char *s, int c, int n, int needfree)
{
	int		i;
	char	*t;

	n = (n == 0) ? ft_strlen(s) : n;
	i = 0;
	while (s[i] == c && i < n)
		i++;
	t = ft_strsub(s, i, ft_strlen(s) - i);
	needfree == 1 ? free(s) : 0;
	return (t);
}

void	ft_realpart(t_ld *list)
{
	int		i;
	int		k;

	list->num = ft_strdup("0");
	ft_arrrev(list->num2);
	i = -1;
	k = list->pwr > 63 ? list->pwr - 63 : 0;
	while (list->num2[++i])
		list->num = ft_strrev(ft_strsum(ft_strrev(list->num, 1),
		ft_strrev((list->num2[i] == '1') ?
		ft_pwr2(i + k) : ft_strdup("0"), 1)), 1);
	list->num = ft_strdrop(list->num, '0', 0, 1);
	list->num = list->ld[0] == '1' ?
	ft_strjoin_free("-", list->num, 0, 1) : list->num;
}

void	ft_ld(long double d)
{
	t_ld *list;

	list = ft_lstcrt(d);
	list->num = (ft_isdigit(list->num[0]) || (ft_isdigit(list->num[1]) &&
	list->num[0] == '-')) ? ft_strjoin_free(ft_strjoinchar(list->num, '.', 1),
	list->mant, 1, 0) : list->num;
	printf(">%s\n", list->num);
	free(list->mant);
	free(list->num);
	free(list);
}

int		main()//int argc, char **argv)
{
	//long double n = -10118888897.001002;
	//long double n = -101188888.001002;
	long double n = -8886666668.001002;
	//long double n = -0.99999994001;
	//n = n * n * n * n * n * n * n;
	//n = n * n * n * n * n * n * n;
	//n = n * n;
	//n = n * n;
	//n = n * n;

	//ft_print_bit2(&n, sizeof(n), 1);

	// long *ptr;
	// ptr = ((long *)(&n));
	// *ptr = 0x8000000000000000;
	//
	// ptr = ((long *)(&n) + 1);
    // *ptr = 0x0000000000007fff;

	//*ptr = *ptr | 0x0000000000008000;

	// int i = 0;
	// while(i < 1000)
	// {
		//ft_print_bit2(&n, sizeof(n), 1);
		ft_ld(n);
		printf("%.7Lf\n", n);
		// printf("%d - ", i);
		// printf("%s\n", s);
	//printf("%.5Lf\n", n);
	// 	i++;
	// }
	return (0);
}
