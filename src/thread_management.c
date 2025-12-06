/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 19:50:58 by jde-carv          #+#    #+#             */
/*   Updated: 2025/12/06 20:09:05 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	join_all_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->nbr_philo)
	{
		pthread_join(sim->philosopher[i].thread_id, NULL);
		i++;
	}
	pthread_join(sim->monitor_thread, NULL);
}

t_simulation	*start_simulation(char **av)
{
	t_simulation	*sim;

	sim = init_simulation(av);
	if (!sim)
		return (NULL);
	if (!init_mutexes(sim))
	{
		clean_simulation(sim);
		return (NULL);
	}
	if (!init_philos(sim))
	{
		clean_simulation(sim);
		return (NULL);
	}
	if (!start_threads(sim))
	{
		return (NULL);
	}
	return (sim);
}

int	start_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->start_simulation = get_actual_time_ms();
	while (i < sim->nbr_philo)
	{
		if (pthread_create(&sim->philosopher[i].thread_id, NULL, &philo_routine,
				&sim->philosopher[i]) != 0)
		{
			sim->end_simulation = 1;
			return (0);
		}
		i++;
	}
	if (pthread_create(&sim->monitor_thread, NULL, &routine_supervisor,
			sim) != 0)
	{
		sim->end_simulation = 1;
		return (0);
	}
	return (1);
}
