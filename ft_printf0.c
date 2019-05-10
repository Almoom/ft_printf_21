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

// unsigned clear_bit(unsigned aValue, unsigned aNumber)
// {
//   return aValue & (~(1 << aNumber));
// }

char	*ft_strnzero(char *s, size_t n)
{
	size_t i;
	char *arr;
	int len;

	i = -1;
	arr = "0";
	len = ft_strlen(s);
	while (++i < n - len)
		s = ft_strjoin_free(s, arr, 1, 0);
	return (s);
}

char	*ft_strsum(char *s1, char *s2)
{
	int i;
	char *sum;
	size_t max;

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

char	*ft_strcptlz(char *s, int c, int flag)
{
	if (!flag)
		while (*s == c)
			s++;
	else
	{
		s = ft_strrev_free(s, 0);
		while (*s == c)
			s++;
		s = ft_strrev_free(s, 0);
	}
	return (s);
}

char	*ft_strncptlz(char *s, int c, int n, int flag)
{
	int i;

	i = 0;
	if (!flag)
		while (*s == c && i < n)
		{
			i++;
			s++;
		}
	else
	{
		s = ft_strrev_free(s, 0);
		while (*s == c && i < n)
		{
			i++;
			s++;
		}
		s = ft_strrev_free(s, 0);
	}
	return (s = ft_strdup(s));
}

char	*ft_strjoinchar(char *s, char c, int flag)
{
	char	*t;
	size_t	i;
	size_t	l;

	i = -1;
	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (l + 1 == 0 || !(t = ft_strnew(l + 1)))
		return (NULL);
	while (++i < l)
		t[i] = s[i];
	t[i] = c;

	flag == 1 ? free(s) : 0;
	return (t);
}

char	*ft_strdvd(char *s, size_t len, int pwr)
{
	char *rez;
	int i;
	char *mask;

	while (pwr-- > 0)
	{
		i = -1;
		mask = ft_strnew(0);
		rez = ft_strnew(0);
		while (s[++i])
		{
			rez = ft_strjoinchar(rez, (s[i] - '0') / 2 + '0', 1);
			if ((s[i] - '0') % 2 == 0)
				mask = ft_strjoin_free(mask, "0", 1, 0);
			else
			{
				mask = ft_strjoin_free(mask, "5", 1, 0);
				rez = (!s[i + 1]) ? ft_strjoin_free(rez, "0", 1, 0) : rez;
			}
		}
		rez = ft_strrev_free(ft_strsum(ft_strrev_free(rez, 1),
		ft_strrev_free(ft_strcptlz(mask, '0', 1), 1)), 1);
		s = ft_strdup(rez);
	}
	return (s = ft_strncptlz(s, '0', len, 0));
}

// int ft_ldround(long double d)
// {
//
// }

int		main()//int argc, char **argv)
{
	// char *str;
	// var("%d", 255, 13);
	// printf("%d %d", 255, 13);
	// var("%s", "test string");
	// var("%c", '&');
	//printf("%d\n", ft_pwr(2, 7));

	// if (argc == 3)
	// {
	// 	ft_putstr(str = ft_itoa_base(ft_atoi(argv[1]), ft_atoi(argv[2])));
	// 	ft_putchar('\n');
	// 	free(str);
	// 	printf("%O\n", ft_atoi(argv[1]));
	// }

	//long double n = 0.01171875;
	long double n = 0.00003;
	// n = n * n *n *n *n *n *n;
	// n = n * n *n *n *n *n *n;
	// n = n * n;
	// n = n * n;
	//n = n * n;

	//long double n = 0.25;
	char *s;
	char *num;
	char *mant;
	char *num2 = "0";
	int i = -1;
	int pwr = 1;
	char *verh;
	char *verh2 = "0";
	char *niz;
	size_t len;
	//long double t;

	ft_print_bit(&n, sizeof(n), 1);
	s = ft_strrev_free(ft_strsub(ft_print_bit(&n, sizeof(n), 0), 48, 16), 1);
	while (++i < 14)
	{
		if (s[14] == '1')
			pwr = (s[i] == '1') ? pwr + ft_atoi(ft_pwr2(i)) : pwr;
		else
			pwr = (s[i] == '0') ? pwr + ft_atoi(ft_pwr2(i)) : pwr;
	}
	pwr = (s[14] == '1') ? pwr : 1 - pwr;
	printf("%d\n", pwr);
	free(s);
	i = -1;
	s = ft_strsub(ft_print_bit(&n, sizeof(n), 0), 64, 64);
	printf("%s\n", s);
	if (pwr >= 0)
	{
		num = ft_strrev_free(ft_strsub(s, 0, pwr + 1), 1);
		while (num[++i])
			num2 = ft_strrev_free(ft_strsum(ft_strrev_free(num2, 0), ft_strrev_free((num[i] == '1') ? ft_pwr2(i) : "0", 0)), 1);
		//printf("%s\n", num2);
		/*printf("%s\n", */mant = ft_strsub(s, pwr + 1, 64)/*)*/;
	}
	else
	{
		mant = s;
		while (++i < -pwr - 1)
			mant = ft_strjoin_free("0", mant, 0, 1);
		//printf("%s\n", mant);

	}
	/*printf("%s\n", */mant = ft_strcptlz(mant, '0', 1)/*)*/;
	len = ft_strlen(mant);
	i = -1;
	verh = ft_strrev_free(mant, 1);
	while (verh[++i])
		verh2 = ft_strrev_free(ft_strsum(ft_strrev_free(verh2, 0), ft_strrev_free((verh[i] == '1') ? ft_pwr2(i) : "0", 0)), 1);
	printf("%s\n", verh2);
	niz = ft_pwr2(ft_strlen(verh));
	printf("%s\n", niz);
	//printf("%zu\n", len);
	// printf("%.100Lf\n", n);
	// printf("%.5Le\n", n);
	//printf("%s\n", ft_strdvd("3", 8));

	printf("%s\n", ft_strdvd(verh2, ft_strlen(verh2), len));
	// printf("%s\n", ft_strncptlz(ft_strdvd(verh2, len), '0', len / 3.3, 0));


	return 0;
}
