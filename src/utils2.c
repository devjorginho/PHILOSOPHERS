/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:46:50 by devjorginho       #+#    #+#             */
/*   Updated: 2025/12/04 20:47:51 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int has_philo(char *av)
{
    if (ft_strncmp(av, "0", 2) == 0 || ft_strncmp(av, "+0", 2) == 0)
        return (0);
    return (1);
}

long long get_actual_time_ms(void)
{
    struct timeval tv;
    long long res;
    
    if (gettimeofday(&tv, NULL) != 0)
        return (0);
    res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (res);
}

long long get_simulation_time_ms(t_simulation *sim)
{
    long long res;
    
    res = get_actual_time_ms() - sim->start_simulation;
    return (res);
}

void ft_usleep(long long time_ms)
{
    long long start_time;

    start_time = get_actual_time_ms();
    while (get_actual_time_ms() < start_time + time_ms)
        usleep(500);
}
