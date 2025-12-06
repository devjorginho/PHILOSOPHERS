/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 21:07:13 by devjorginho       #+#    #+#             */
/*   Updated: 2025/12/06 16:31:06 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static t_simulation	*alloc_simulation(void)
{
	t_simulation	*sim;

	sim = ft_calloc(1, sizeof(t_simulation));
	if (!sim)
		return (NULL);
	return (sim);
}

static t_simulation	*populate_simulation(t_simulation *sim, char **av)
{
	sim->nbr_philo = ft_atol(av[1]);
	sim->time_to_die = ft_atol(av[2]);
	sim->time_to_eat = ft_atol(av[3]);
	sim->time_to_sleep = ft_atol(av[4]);
	if (!av[5])
		sim->limit_meals = -1;
	else
		sim->limit_meals = ft_atol(av[5]);
	sim->end_simulation = 0;
	return (sim);
}

t_simulation	*init_simulation(char **av)
{
	t_simulation	*sim;

	if (!has_philo(av[1]))
		return (NULL);
	sim = alloc_simulation();
	if (!sim)
		return (NULL);
	if (!populate_simulation(sim, av))
	{
		free(sim);
		return (NULL);
	}
	return (sim);
}
