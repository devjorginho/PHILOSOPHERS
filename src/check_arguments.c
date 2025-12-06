/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:36:52 by devjorginho       #+#    #+#             */
/*   Updated: 2025/12/06 11:44:49 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	is_number(const char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	if (s[0] == '+')
		i = 1;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	is_positive(const char *s)
{
	long int	res;
	int			i;

	i = 0;
	if (!s || !*s)
		return (0);
	if (s[0] == '+')
		i = 1;
	if (s[i] == '0' && s[i + 1] == '\0' && i == 1)
		return (0);
	res = ft_atol(s + i);
	if (res < 0)
		return (0);
	return (1);
}

static int	check_overflow(const char *s)
{
	if (ft_atol(s) > INT_MAX)
		return (0);
	return (1);
}

static int	check_arguments(const char *s)
{
	if (!is_number(s))
		return (0);
	if (!is_positive(s))
		return (0);
	if (!check_overflow(s))
		return (0);
	return (1);
}

int	validate_arguments(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (0);
	while (i <= 4)
	{
		if (!check_arguments(av[i]))
			return (0);
		i++;
	}
	if (ac == 6)
	{
		if (!check_arguments(av[5]))
			return (0);
	}
	return (1);
}
