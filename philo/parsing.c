/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:36:14 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/07 12:25:54 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdg(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	else
		return (0);
}

int	is_def_digit(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!ft_inv(args[i][j]))
				return (0);
			if (!ft_isdg(args[i][j]))
			{
				if (args[i][j] == '+')
				{
					if (!ft_isdg(args[i][j + 1]))
						return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	parsing(char **av)
{
	int	n;

	n = 0;
	if (!is_full_spaces(av))
		return (0);
	if (!is_def_digit(av))
		return (0);
	while (av[n])
	{
		if (!av[n][0])
			return (0);
		n++;
	}
	if (ft_atoi(av[1]) <= 0)
		return (0);
	return (1);
}

static long	long_n(long n, int neg, int j)
{
	long	nb;

	nb = n;
	if (nb == -2147483648)
		return (-2147483648);
	if (j >= 20 && neg > 0)
		return (-1);
	if (n > LONG_MAX && neg > 0)
		return (-1);
	if (n > LONG_MAX && neg < 0)
		return (0);
	if (j >= 20 && neg < 0)
		return (0);
	return (n * neg);
}

long	ft_atoi(char *str)
{
	int		neg;
	long	n;
	int		j;

	neg = 1;
	j = 0;
	n = 0;
	skip_wspaces(&str);
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (*str == '0')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		n = n * 10 + *str - 48;
		if ((n > INT_MAX && neg == 1) || (n > 2147483648 && neg == -1))
			return (-1);
		str++;
		j++;
	}
	return (long_n(n, neg, j));
}
