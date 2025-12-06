/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 11:44:29 by devjorginho       #+#    #+#             */
/*   Updated: 2025/12/06 16:32:22 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	has_philo(char *av)
{
	if (ft_strncmp(av, "0", 2) == 0 || ft_strncmp(av, "+0", 2) == 0)
		return (0);
	return (1);
}

long long	get_actual_time_ms(void)
{
	struct timeval	tv;
	long long		res;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (res);
}

long long	get_simulation_time_ms(t_simulation *sim)
{
	long long	res;

	res = get_actual_time_ms() - sim->start_simulation;
	return (res);
}

void	ft_usleep(long long time_ms)
{
	long long	start_time;
	long long	target_time;

	start_time = get_actual_time_ms();
	target_time = start_time + time_ms;
	while (get_actual_time_ms() < target_time)
		usleep(100);
}
