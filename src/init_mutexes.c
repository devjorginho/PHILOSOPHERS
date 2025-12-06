/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:31:51 by devjorginho       #+#    #+#             */
/*   Updated: 2025/12/06 10:23:13 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	alloc_forks(t_simulation *sim, int n_forks)
{
	sim->forks = ft_calloc(n_forks, sizeof(pthread_mutex_t));
	if (!sim->forks)
		return (0);
	return (1);
}

static void	destroy_forks(t_simulation *sim, int n_initialized)
{
	int	i;

	i = 0;
	if (!sim || !sim->forks)
		return ;
	while (i < n_initialized)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	free(sim->forks);
	sim->forks = NULL;
}

static int	init_forks(t_simulation *sim)
{
	int	i;

	i = 0;
	if (!sim || !sim->forks)
		return (0);
	while (i < sim->nbr_philo)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			destroy_forks(sim, i);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_general_mutexes(t_simulation *sim)
{
	if (pthread_mutex_init(&sim->print_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&sim->simulation_lock, NULL) != 0)
		return (0);
	return (1);
}

int	init_mutexes(t_simulation *sim)
{
	if (!alloc_forks(sim, sim->nbr_philo))
		return (0);
	if (!init_forks(sim))
		return (0);
	if (!init_general_mutexes(sim))
	{
		destroy_forks(sim, sim->nbr_philo);
		return (0);
	}
	return (1);
}
