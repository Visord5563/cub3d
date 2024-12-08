/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:46:43 by saharchi          #+#    #+#             */
/*   Updated: 2024/12/08 22:55:15 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

#define MAX_LL LLONG_MAX

static long long	result(const char *s, int i, int sign)
{
	long long	r;

	r = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (r > MAX_LL / 10 || (r == MAX_LL / 10 && (s[i] - '0') > MAX_LL % 10))
		{
			if (sign == -1)
				return (LLONG_MIN);
			return (LLONG_MAX);
		}
		r = r * 10 + (s[i] - '0');
		i++;
	}
	return (r);
}

long long	ft_atoll(const char *str)
{
	int			i;
	long long	r;
	int			s;

	i = 0;
	s = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	r = result(str, i, s);
	return (r * s);
}
