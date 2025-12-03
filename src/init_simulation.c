/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:30:31 by devjorginho       #+#    #+#             */
/*   Updated: 2025/12/03 18:26:55 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	has_philo(char *av)
{
	if((ft_strncmp(av[1], "+0", 2) == 0) || av[0] == '0')
		return (0);
	return (1);
}
static t_simulation *alloc_simulation(void)
{
    t_simulation *sim;

    sim = ft_calloc(1, sizeof(t_simulation));
    if (!sim)
        return NULL;
    return sim;
}

static t_simulation	*populate_simulation(t_simulation *sim, char **av)
{
	sim->nbr_philo = ft_atol(av[1]);
	sim->time_to_die = ft_atol(av[2]);
	sim->time_to_eat = ft_atol(av[3]);
	sim->time_to_sleep = ft_atol(av[4]);
	if(!av[5])
		sim->limit_meals = -1;
	else
		sim->limit_meals = ft_atol(av[5]);
	return (sim);
}

static t_simulation *gettime_simulation(t_simulation *sim)
{
	struct timeval tv;

	if (!sim)
		return NULL;
	if (gettimeofday(&tv, NULL) != 0)
		return NULL;
	sim->start_simulation = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (sim);
}

t_simulation *new_simulation(char **av)
{
	t_simulation *sim;
	
	if(!has_philo(av[1]))
		return (NULL);
	sim = alloc_simulation();
	if(!sim)
		return (NULL);
	sim = populate_simulation(sim, av);
	sim = gettime_simulation(sim);
	return (sim);
}
