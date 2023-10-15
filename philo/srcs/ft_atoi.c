/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:06:33 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/15 11:02:37 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static char	*ft_space(char *s)
{
	while (*s == ' ' || ('\t' <= *s && *s <= '\r'))
		s++;
	return (s);
}

static	long	ft_plus_calu(char *str)
{
	long			div;
	long			mod;
	long			res;
	unsigned int	n;

	div = LONG_MAX / 10;
	mod = LONG_MAX % 10;
	res = 0;
	while ('0' <= *str && *str <= '9')
	{
		n = (*str - '0');
		if (res > div || (res == div && n > mod))
			return (LONG_MAX);
		res = 10 * res + n;
		str++;
	}
	return (res);
}

static long	ft_minus_calu(const char *str)
{
	long		div;
	long		mod;
	long		res;
	signed int	n;

	div = LONG_MIN / 10;
	mod = LONG_MIN % 10;
	res = 0;
	while ('0' <= *str && *str <= '9')
	{
		n = - (*str - '0');
		if (res < div || (res == div && n < mod))
			return (LONG_MIN);
		res = (10 * res) + n;
		str++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	char	*copy_str;

	copy_str = (char *)str;
	copy_str = ft_space(copy_str);
	if (*copy_str == '-')
	{
		copy_str++;
		return ((int) ft_minus_calu(copy_str));
	}
	else if (*copy_str == '+')
		copy_str++;
	return ((int) ft_plus_calu(copy_str));
}

// #include <stdio.h>
// int main()
// {
// 	printf("atoi    %d\n", atoi("9223372036854775808"));
// 	printf("ft_atoi    %d\n", ft_atoi("9223372036854775808"));
// 	// printf("ft_atoi %d\n", ft_atoi("92233720368547754648665808"));
// 	printf("atoi    %d\n", atoi("\t\v\f\r\n \f-06050"));
// 	printf("ft_atoi %d\n", ft_atoi("\t\v\f\r\n \f-06050"));
// 	printf("atoi    %d\n", atoi("  -3"));
// 	printf("ft_atoi %d\n", ft_atoi("  -3"));
// 	printf("atoi    %d\n", atoi("+4141"));
// 	printf("ft_atoi %d\n", ft_atoi("+4141"));
// 	printf("atoi    %d\n", atoi("jfalk"));
// 	printf("ft_atoi %d\n", ft_atoi("jfalk"));
// 	printf("atoi    %d\n", atoi("12313"));
// 	printf("ft_atoi %d\n", ft_atoi("12313"));
// 	printf("atoi    %d\n", atoi("---0123"));
// 	printf("ft_atoi %d\n", ft_atoi("---0123"));
// 	printf("atoi    %d\n", atoi("---1123"));
// 	printf("ft_atoi %d\n", ft_atoi("---1123"));
// 	printf("atoi    %d\n", atoi("-1123"));
// 	printf("ft_atoi %d\n", ft_atoi("-1123"));
// 	printf("atoi    %d\n", atoi("++1123"));
// 	printf("ft_atoi    %d\n", ft_atoi("++1123"));
// }