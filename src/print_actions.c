/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 20:00:33 by jde-carv          #+#    #+#             */
/*   Updated: 2025/12/06 20:07:18 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	print_actions(t_philo *philo, char *status_msg)
{
	long long		time;
	t_simulation	*sim;

	sim = philo->sim;
	pthread_mutex_lock(&sim->print_lock);
	if (sim->end_simulation == 0)
	{
		time = get_simulation_time_ms(sim);
		printf("%lld %d %s\n", time, philo->id, status_msg);
	}
	pthread_mutex_unlock(&sim->print_lock);
}

void	philo_sleep(t_philo *philo)
{
	if (is_simulation_finished(philo->sim))
		return ;
	print_actions(philo, "is sleeping");
	if (!is_simulation_finished(philo->sim))
		ft_usleep(philo->sim->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	if (is_simulation_finished(philo->sim))
		return ;
	print_actions(philo, "is thinking");
}

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_eat(t_philo *philo)
{
	t_simulation	*sim;

	sim = philo->sim;
	pthread_mutex_lock(philo->left_fork);
	if (is_simulation_finished(sim))
		return ((void)pthread_mutex_unlock(philo->left_fork));
	print_actions(philo, "has taken a fork");
	if (sim->nbr_philo == 1)
		return ((void)has_one_philo(sim, philo));
	pthread_mutex_lock(philo->right_fork);
	if (is_simulation_finished(sim))
		return ((void)unlock_forks(philo));
	print_actions(philo, "has taken a fork");
	print_actions(philo, "is eating");
	pthread_mutex_lock(&sim->simulation_lock);
	philo->last_meal_time = get_simulation_time_ms(sim);
	philo->meals_count++;
	pthread_mutex_unlock(&sim->simulation_lock);
	if (!is_simulation_finished(sim))
		ft_usleep(sim->time_to_eat);
	unlock_forks(philo);
}
