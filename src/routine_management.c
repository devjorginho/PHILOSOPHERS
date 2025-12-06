/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 11:54:13 by devjorginho       #+#    #+#             */
/*   Updated: 2025/12/06 20:06:19 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	philo_cycle_of_life(t_philo *philo)
{
	t_simulation	*sim;

	sim = philo->sim;
	philo_eat(philo);
	pthread_mutex_lock(&sim->simulation_lock);
	if (sim->limit_meals != -1 && philo->meals_count >= sim->limit_meals)
	{
		pthread_mutex_unlock(&sim->simulation_lock);
		return (1);
	}
	pthread_mutex_unlock(&sim->simulation_lock);
	philo_sleep(philo);
	philo_think(philo);
	if (sim->nbr_philo % 2 != 0)
	{
		usleep(100);
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	t_simulation	*sim;

	philo = (t_philo *)arg;
	sim = philo->sim;
	pthread_mutex_lock(&sim->simulation_lock);
	philo->last_meal_time = get_simulation_time_ms(sim);
	if (sim->limit_meals == 0)
	{
		pthread_mutex_unlock(&sim->simulation_lock);
		return (NULL);
	}
	pthread_mutex_unlock(&sim->simulation_lock);
	if (philo->id % 2 == 0)
		ft_usleep(sim->time_to_eat / 2);
	while (!is_simulation_finished(sim))
	{
		if (philo_cycle_of_life(philo))
			break ;
	}
	return (NULL);
}

static int	supervisor_check_state(t_simulation *sim)
{
	int	all_meals_done;
	int	i;

	all_meals_done = 1;
	i = -1;
	while (++i < sim->nbr_philo)
	{
		if (check_death(&sim->philosopher[i], sim))
			return (1);
		if (sim->limit_meals != -1)
		{
			pthread_mutex_lock(&sim->simulation_lock);
			if (sim->philosopher[i].meals_count < sim->limit_meals)
				all_meals_done = 0;
			pthread_mutex_unlock(&sim->simulation_lock);
		}
	}
	if (sim->limit_meals != -1 && all_meals_done)
	{
		pthread_mutex_lock(&sim->simulation_lock);
		sim->end_simulation = 1;
		pthread_mutex_unlock(&sim->simulation_lock);
		return (1);
	}
	return (0);
}

void	*routine_supervisor(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	if (sim->limit_meals == 0)
	{
		pthread_mutex_lock(&sim->simulation_lock);
		sim->end_simulation = 1;
		pthread_mutex_unlock(&sim->simulation_lock);
		return (NULL);
	}
	usleep(100);
	while (!is_simulation_finished(sim))
	{
		if (supervisor_check_state(sim))
			break ;
		usleep(50);
	}
	return (NULL);
}
