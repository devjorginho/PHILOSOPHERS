/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 11:45:40 by devjorginho       #+#    #+#             */
/*   Updated: 2025/12/06 11:45:43 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void print_actions(t_philo *philo, char *status_msg)
{
    long long time;
    t_simulation *sim;

    sim = philo->sim;
    
    pthread_mutex_lock(&sim->print_lock);
    if (sim->end_simulation == 0)
    {
        time = get_simulation_time_ms(sim);
        printf("%lld %d %s\n", time, philo->id, status_msg);
    }
    pthread_mutex_unlock(&sim->print_lock);
}

void philo_sleep(t_philo *philo)
{
    if (is_simulation_finished(philo->sim))
        return ;
    print_actions(philo, "is sleeping");
    if (!is_simulation_finished(philo->sim))
        ft_usleep(philo->sim->time_to_sleep); 
}

void philo_think(t_philo *philo)
{
    if (is_simulation_finished(philo->sim))
        return ;
        
    print_actions(philo, "is thinking");
}

void philo_eat(t_philo *philo)
{
    t_simulation *sim;

    sim = philo->sim;
    pthread_mutex_lock(philo->left_fork);
    if (is_simulation_finished(sim))
    {
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    print_actions(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    if (is_simulation_finished(sim))
    {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    print_actions(philo, "has taken a fork");
    print_actions(philo, "is eating");
    pthread_mutex_lock(&sim->simulation_lock);
    philo->last_meal_time = get_simulation_time_ms(sim);
    philo->meals_count++;
    pthread_mutex_unlock(&sim->simulation_lock);
    if (!is_simulation_finished(sim))
        ft_usleep(sim->time_to_eat);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}
