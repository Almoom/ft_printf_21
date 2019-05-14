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

#define  TEST1

void var(char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	if(!ft_strcmp(format, "%d"))
	{
		int x = va_arg (ap, int);
		//printf ("You passed decimal object with value %d\n", x);
		ft_putstr("You passed decimal object with value ");
		ft_putstr(ft_itoa(x));
		ft_putchar('\n');
	}
	if(!ft_strcmp(format, "%d"))
	{
		int y = va_arg (ap, int);
		//printf ("You passed decimal object with value %d\n", x);
		ft_putstr("You passed decimal object with value ");
		ft_putstr(ft_itoa(y));
		ft_putchar('\n');
	}

	if(!ft_strcmp(format, "%s"))
	{
		char *p = va_arg (ap, char *);
		//printf ("You passed c-string \"%s\"\n", p);
		ft_putstr("You passed c-string \"");
		ft_putstr(p);
		ft_putstr("\"");
		ft_putchar('\n');
	}

	if(!ft_strcmp(format, "%c"))
	{
		int c = va_arg (ap, int);
		//printf ("You passed 1 char \'%c\'\n", (unsigned char)c);
		ft_putstr("You passed 1 char \'");
		ft_putchar((unsigned char)c);
		ft_putstr("\'");
		ft_putchar('\n');
	}
	va_end (ap);
}

static char	*ft_calc_bit(int n)
{
	char *s;
	char arr[2];

	ft_bzero(arr, 2);
	s = ft_strnew(0);
	while (n > 0)
	{
		arr[0] = n % 2 + '0';
		s = ft_strjoin_free(s, arr, 1, 0);
		n /= 2;
	}
	s = ft_strrev_free(s, 1);
	while (ft_strlen(s) < 8)
		s = ft_strjoin_free("0", s, 0, 1);
	return (s);
}

char		*ft_print_bit2(void *v, int size, int flag)
{
	char *s;

	s = ft_strnew(0);
	while (size-- > 0)
	{
		s = ft_strjoin_free(s, ft_calc_bit(*((unsigned char *)v + size)), 1, 0);
		flag == 1 ? ft_putstr(ft_calc_bit(*((unsigned char *)v + size))) : 0;
		flag == 1 ? ft_putstr(size > 0 ? "__" : "\n") : 0;
	}
	return (flag == 1 ? NULL : s);
}

// char	*ft_strcptlz(char *s, int c, int flag)
// {
// 	if (!flag)
// 		while (*s == c)
// 			s++;
// 	else
// 	{
// 		s = ft_strrev_free(s, 0);
// 		while (*s == c)
// 			s++;
// 		s = ft_strrev_free(s, 0);
// 	}
// 	return (s);
// }

// unsigned clear_bit(unsigned aValue, unsigned aNumber)
// {
//   return aValue & (~(1 << aNumber));
// }

char *ft_itoa_base(int n, int base)
{
	char *s;
	char arr[2] = {0, 0};
	unsigned int num;

	num = (unsigned int)n;
	s = ft_strnew(0);
	while(num > 0)
	{
		if (base == 8 || base == 16)
		{
			arr[0] = num % base + (num % base > 9 ? 'A' - 10 : '0');
			s = ft_strjoin_free(s, arr, 1, 0);
		}
		else if (base == 10)
			return (ft_itoa(n));
		else
			exit(0) ;
		num /= base;
	}
	return (s = ft_strrev_free(s, 1));
}

char	*ft_strnzero(char *s, size_t n)
{
	size_t	i;
	int		len;

	i = -1;
	len = ft_strlen(s);
	while (++i < n - len)
	{
		s = ft_strjoinchar(s, '0', 0);
	}
	return (s);
}

int 	ft_flagfree(int a, int b)
{
	if (a == b)
		return (-1);
	return (a < b ? 0 : 1);
}

char	*ft_strsum(char *s1, char *s2)
{
	int i;
	char *sum;
	size_t max;
	int flag;

	flag = ft_flagfree(ft_strlen(s1), ft_strlen(s2));
	max = (ft_strlen(s1) > ft_strlen(s2)) ? ft_strlen(s1) : ft_strlen(s2);
	s1 = ft_strnzero(s1, max);
	s2 = ft_strnzero(s2, max);
	sum = ft_memset(ft_strnew(max + 1), '0', max);
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
	if (flag != -1)
		flag == 0 ? free(s1) : free(s2);
	return (sum);
}

char	*ft_pwr2(int pwr)
{
	char *t;

	t = "1";
	while (pwr-- > 0)
		t = ft_strsum(t, t);
	return (t = ft_strrev_free(t, 0));
}

char	*ft_strncptlz(char *s, int c, int n, int withend)
{
	int i;

	i = (n == 0) ? -ft_strlen(s) : 0;
	if (!withend)
		while (*s == c && i++ < n)
			s++;
	else
	{
		s = ft_strrev_free(s, 0);
		while (*s == c && i++ < n)
			s++;
		s = ft_strrev_free(s, 0);
	}
	return (s);
}

char *ft_ldaccuracy(char *s, int t, int len)
{
	s = (int)ft_strlen(s) > t + len ? ft_strsub_free(s, 0, t + len + 1, 1) : s;
	return (s);
}

char	*ft_strdvd(char *s, size_t len, int pwr, int acc)
{
	char *rez;
	char *mask;

	while (pwr-- > 0)
	{
		mask = ft_strdup("0");
		rez = ft_strnew(0);
		while (*s)
		{
			rez = ft_strjoinchar(rez, (*s - '0') / 2 + '0', 1);
			mask = ft_strjoinchar(mask, ((*s - '0') % 2 == 0) ? '0' : '5', 1);
			rez = !s[1] && (*s - '0') % 2 == 1 ?
			ft_strjoinchar(rez, '0', 1) : rez;
			s++;
		}
		rez = ft_strrev_free(ft_strsum(ft_strrev_free(rez, 1),
		ft_strrev_free(ft_strncptlz(mask, '0', 1, 1), 1)), 1);
		s = ft_ldaccuracy(rez, acc, len);

	}
	while (ft_strlen(s) < (size_t)acc + 1 + len)
		s = ft_strjoinchar(s, '0', 0);
	return (s = ft_strncptlz(s, '0', len, 0));
}

int		ft_ldpwr(long double *d)
{
	char *s;
	char *t;
	int pwr;
	size_t i;

	i = -1;
	pwr = 1;
	t = ft_print_bit(d, sizeof(*d));
	s = ft_strrev_free(ft_strsub(t, 48, 16), 1);
	free(t);
	while (++i < 14)
	{
		if (s[14] == '1')
			pwr = (s[i] == '1') ? pwr + ft_atoi(ft_pwr2(i)) : pwr;
		else
			pwr = (s[i] == '0') ? pwr + ft_atoi(ft_pwr2(i)) : pwr;
	}
	pwr = (s[14] == '1') ? pwr : 1 - pwr;
	free(s);
	return (pwr);
}

char	*ft_realpart(char *s, int pwr, int znak)
{
	int		i;
	int		k;
	char 	*num;
	char 	*num2;

	i = -1;
	num2 = "0";
	k = pwr > 63 ? pwr - 63 : 0;
	num = ft_strrev_free(ft_strsub(s, 0, pwr + 1), 1);
	while (num[++i])
		num2 = ft_strrev_free(ft_strsum(ft_strrev_free(num2, 0),
		ft_strrev_free((num[i] == '1') ? ft_pwr2(i + k) : "0", 0)), 1);
	return (znak ? ft_strjoin_free("-", num2, 0, 1) : num2);
}

char	*ft_unrealpart(char *s)
{
	int		i;
	size_t	len;
	char	*verh2;

	i = -1;
	verh2 = "0";
	len = ft_strlen(s);
	while (s[++i])
		verh2 = ft_strrev_free(ft_strsum(ft_strrev_free(verh2, 0),
		ft_strrev_free((s[i] == '1') ? ft_pwr2(i) : "0", 0)), 1);
	return (ft_strdvd(verh2, ft_strlen(verh2), len, 5));
}

char *ft_ldround(char *num, char *mant, int c)
{
	if (mant[ft_strlen(mant) - 1] > '4')
		mant = (mant[ft_strlen(mant) - 2] == '9') ?
		ft_strrev_free(ft_strsum(ft_strrev_free(ft_strsub_free
		(mant, 0, ft_strlen(mant) - 1, 0), 0), "1"), 1) : ft_strjoinchar
		(ft_strsub_free(mant, 0, ft_strlen(mant) - 2, 0), c + 1, 1);
	else
		mant = ft_strjoinchar
		(ft_strsub_free(mant, 0, ft_strlen(mant) - 2, 0), c, 1);
	num = (ft_isdigit(num[0]) || (ft_isdigit(num[1]) && num[0] == '-')) ?
	ft_strjoin_free(ft_strjoinchar(num, '.', 0), mant, 1, 1) : num;
	return (num);
}

char *ft_ldseparat(char *s, int pwr, int c)
{
	char *num;
	char *mant;
	int i;

	mant = "";
	i = -1;
	if (pwr == 16384 && ft_strchr(s + 1, '1'))
		num = "nan";
	else if (pwr == 16384 && !ft_strchr(s + 1, '1'))
		num = (c == '0') ? "inf" : "-inf";
	else if (pwr >= 0)
	{
		num = ft_realpart(s, pwr, (c - 48));
		mant = ft_strsub(s, pwr + 1, 64);
	}
	else
	{
		num = (c - 48) ? "-0" : "0";
		mant = s;
		while (++i < -pwr - 1)
			mant = ft_strjoin_free("0", mant, 0, 1);
	}
	mant = ft_unrealpart(ft_strrev_free(ft_strncptlz(mant, '0', 0, 1), 1));
	return (ft_ldround(num, mant, mant[ft_strlen(mant) - 2]));
}

char	*ft_ld(long double *d)
{
	char *s;
	int pwr;

	pwr = ft_ldpwr(d);
	s = ft_strsub(ft_print_bit(d, sizeof(*d)), 64, 64);
	return (ft_ldseparat(s, ft_ldpwr(d), ft_print_bit(d, sizeof(*d))[48]));
}

int		main()//int argc, char **argv)
{

	char *s;
	// var("%d", 255, 13);
	// printf("%d %d", 255, 13);
	// var("%s", "test string");
	// var("%c", '&');
	// printf("%d\n", ft_pwr(2, 7));
	//
	// if (argc == 3)
	// {
	// 	ft_putstr(str = ft_itoa_base(ft_atoi(argv[1]), ft_atoi(argv[2])));
	// 	ft_putchar('\n');
	// 	free(str);
	// 	printf("%O\n", ft_atoi(argv[1]));
	// }

	long double n = 770.000009;
	//long double n = 0.25;
	//int n = 10;
	//n = n * n * n * n * n * n * n;
	//n = n * n * n * n * n * n * n;
	//n = n * n;
	//n = n * n;
	//n = n * n;

	// s = ft_print_bit(&n, sizeof(n), 0);
	// printf("%s\n", s);
	// free(s);

	// s = ft_strsum("34", "110");
	// printf("%s\n", s);
	// free(s);
	//s = ft_pwr2(1);

	//printf("%s\n", s);
	//free(s);

	// long *ptr;
	// ptr = ((long *)(&n));
	// *ptr = 0x8000000000000000;
	//
	// ptr = ((long *)(&n) + 1);
    // *ptr = 0x0000000000007fff;

	// *ptr = *ptr | 0x0000000000008000;
		s = ft_ld(&n);
		printf("%s\n", s);
		free(s);
	//printf("%.5Lf\n", n);



	return (0);
}
