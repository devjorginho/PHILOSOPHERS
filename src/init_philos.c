/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 19:36:22 by devjorginho       #+#    #+#             */
/*   Updated: 2025/12/06 10:25:28 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	alloc_philos(t_simulation *sim)
{
	sim->philosopher = ft_calloc(sim->nbr_philo, sizeof(t_philo));
	if (!sim->philosopher)
		return (0);
	return (1);
}

int	init_philos(t_simulation *sim)
{
	int		i;
	int		right_fork_index;
	t_philo	*philo;

	if (!alloc_philos(sim))
		return (0);
	i = 0;
	while (i < sim->nbr_philo)
	{
		philo = &sim->philosopher[i];
		philo->id = i + 1;
		philo->meals_count = 0;
		philo->last_meal_time = sim->start_simulation;
		philo->sim = sim;
		right_fork_index = (i + 1) % sim->nbr_philo;
		philo->left_fork = &sim->forks[i];
		philo->right_fork = &sim->forks[right_fork_index];
		if (philo->id % 2 != 0)
		{
			philo->left_fork = &sim->forks[right_fork_index];
			philo->right_fork = &sim->forks[i];
		}
		i++;
	}
	return (1);
}
