/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.data->c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:12:40 by hsawamur          #+#    #+#             */
/*   Updated: 2024/01/15 23:02:46 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_strtol
{
	unsigned long	n;
	int				symbol;
	long			range;
	unsigned long	divided;
	int				modulus;
	int				base;
	int				c;
}	t_strtol;

static int	get_speceific_base(char **s, int base)
{
	if ((*s)[0] != '\0'
		&& ((*s)[0] == '0' && ((*s)[1] == 'x' || (*s)[1] == 'X'))
		&& (base == 0 || base == 16))
	{
		(*s) += 2;
		base = 16;
	}
	if (base == 0)
	{
		if (**s == '0')
			base = 8;
		else
			base = 10;
	}
	return (base);
}

static int	get_c(char *str)
{
	if ('0' <= (*str) && (*str) <= '9')
		return ((*str) - '0');
	else if ('a' <= (*str) && (*str) <= 'z')
		return (*str - ('a' - 10));
	else if ('A' <= (*str) && (*str) <= 'Z')
		return (*str - ('A' - 10));
	return (*str);
}

static long	strtol_until(t_strtol *data, char *str, char **endptr)
{
	unsigned long	res;

	res = 0;
	while (*str != '\0')
	{
		data->c = get_c(str);
		if (data->c >= data->base)
			break ;
		if (res > data->divided
			|| (res == data->divided && data->c > data->modulus))
		{
			if (endptr != NULL)
				*endptr = str;
			return (data->range);
		}
		res *= data->base;
		res += data->c;
		str++;
	}
	if (endptr != NULL)
		*endptr = str;
	return (res * data->symbol);
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	t_strtol	data;
	char		*str;

	str = (char *)nptr;
	(&data)->symbol = 1;
	while (*str == ' ' || ('\t' <= *str && *str <= '\r'))
		str++;
	if (*str == '-')
	{
		(&data)->symbol = -1;
		(&data)->range = LONG_MIN;
		str++;
	}
	else if (*str == '+')
	{
		(&data)->range = LONG_MAX;
		str++;
	}
	(&data)->c = *str;
	(&data)->base = get_speceific_base(&str, base);
	(&data)->modulus = (&data)->range % (unsigned long)base;
	(&data)->divided = (&data)->range / (unsigned long)base;
	return (strtol_until(&data, str, endptr));
}

// #include <stdlib.h>
// #include <stdio.h>

// static void is_valid(char *endptr)
// {
// 	if (*endptr == '\0')
// 		printf("Valid\n");
// 	else
// 		printf("Not Valid\n");
// }

// int main(void)
// {
// 	const char *str = "ああ";
// 	char *endptr = NULL;
// 	long num = ft_strtol(str, &endptr, 10);

// 	printf("Number: %ld\n", num);
// 	printf("Next character after conversion: %s\n", endptr);

// 	printf("strtol    %ld\n", strtol("922t3372036854775808", &endptr, 10));
// 	is_valid(endptr);
// 	printf("ft_strtol%ld\n", ft_strtol("922t3372036854775808", &endptr, 10));
// 	is_valid(endptr);
// // 	printf("strtol    %ld\n", strtol("\t\v\f\r\n \f-06050", &endptr, 16));
// // 	is_valid(endptr);
// // 	printf("ft_strtol %ld\n", ft_strtol("\t\v\f\r\n \f-06050", &endptr, 16));
// // 	is_valid(endptr);
// // 	printf("strtol    %ld\n", strtol("+4141", &endptr, 16));
// // 	is_valid(endptr);
// // 	printf("ft_strtol %ld\n", ft_strtol("+4141", &endptr, 16));
// // 	is_valid(endptr);
// // 	printf("strtol    %ld\n", strtol("  -3", &endptr, 16));
// // 	is_valid(endptr);
// // 	printf("ft_strtol %ld\n", ft_strtol("  -3", &endptr, 16));
// // 	is_valid(endptr);
// // 	printf("strtol    %ld\n", strtol("jfalk", &endptr, 32));
// // 	is_valid(endptr);
// // 	printf("ft_strtol %ld\n", ft_strtol("jfalk", &endptr, 32));
// // 	is_valid(endptr);
// // 	printf("strtol    %ld\n", strtol("12313", &endptr, 32));
// // 	is_valid(endptr);
// // 	printf("ft_strtol %ld\n", ft_strtol("12313", &endptr, 32));
// // 	is_valid(endptr);
// // 	printf("strtol    %ld\n", strtol("---0123", &endptr, 10));
// // 	is_valid(endptr);
// // 	printf("ft_strtol %ld\n", ft_strtol("---0123", &endptr, 10));
// // 	is_valid(endptr);
// // 	printf("strtol    %ld\n", strtol("---1123", &endptr, 0));
// // 	is_valid(endptr);
// // 	printf("ft_strtol %ld\n", ft_strtol("---1123", &endptr, 0));
// // 	is_valid(endptr);
// // 	printf("strtol    %ld\n", strtol("-1123", &endptr, 10));
// // 	is_valid(endptr);
// // 	printf("ft_strtol %ld\n", ft_strtol("-1123", &endptr, 10));
// // 	is_valid(endptr);
// // 	printf("strtol    %ld\n", strtol("++1123", &endptr, 10));
// // 	is_valid(endptr);
// // 	printf("ft_strtol    %ld\n", ft_strtol("++1123", &endptr, 10));
// // 	is_valid(endptr);
// }
