/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 19:42:52 by devjorginho       #+#    #+#             */
/*   Updated: 2025/12/04 19:50:46 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	destroy_all_forks(t_simulation *sim)
{
	int	i;

	if (!sim || !sim->forks)
		return ;
	i = 0;
	while (i < sim->nbr_philo)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	free(sim->forks);
}

void	clean_simulation(t_simulation *sim)
{
	if (!sim)
		return ;
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->simulation_lock);
	destroy_all_forks(sim);
	if (sim->philosopher)
		free(sim->philosopher);
	free(sim);
}
