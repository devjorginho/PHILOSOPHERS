/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 19:10:18 by jde-carv          #+#    #+#             */
/*   Updated: 2025/12/06 20:06:25 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	has_one_philo(t_simulation *sim, t_philo *philo)
{
	while (!is_simulation_finished(sim))
		usleep(100);
	pthread_mutex_unlock(philo->left_fork);
}

int	is_simulation_finished(t_simulation *sim)
{
	int	result;

	pthread_mutex_lock(&sim->simulation_lock);
	result = sim->end_simulation;
	pthread_mutex_unlock(&sim->simulation_lock);
	return (result);
}

int	check_death(t_philo *philo, t_simulation *sim)
{
	long long	time_since_last_meal;
	long long	current_time;
	int			dead_philo_id;

	pthread_mutex_lock(&sim->simulation_lock);
	current_time = get_simulation_time_ms(sim);
	time_since_last_meal = current_time - philo->last_meal_time;
	if (time_since_last_meal > sim->time_to_die)
	{
		sim->end_simulation = 1;
		dead_philo_id = philo->id;
		pthread_mutex_unlock(&sim->simulation_lock);
		pthread_mutex_lock(&sim->print_lock);
		printf("%llu %d died\n", current_time, dead_philo_id);
		pthread_mutex_unlock(&sim->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&sim->simulation_lock);
	return (0);
}
