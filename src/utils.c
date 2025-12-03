/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:44:19 by devjorginho       #+#    #+#             */
/*   Updated: 2025/11/29 18:44:07 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

long	ft_atol(const char *s)
{
	long	sign;
	long	n;

	sign = 1;
	n = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		n = n * 10 + (*s - '0');
		s++;
	}
	return (n * sign);
}


int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

	i = 0;
    if (n == 0)
        return 0;

    while (i < n && s1[i] && s2[i])
    {
        if ((unsigned char)s1[i] != (unsigned char)s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }

    if (i < n)
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);

    return 0;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*alloc;
	size_t			full_s;

	if (!nmemb || !size)
	{
		alloc = malloc(0);
		if (!alloc)
			return (NULL);
		return (alloc);
	}
	full_s = nmemb * size;
	if (nmemb != full_s / size)
		return (NULL);
	alloc = malloc(full_s);
	if (!alloc)
		return (NULL);
	ft_bzero(alloc, full_s);
	return ((void *)alloc);
}