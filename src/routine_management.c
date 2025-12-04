/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:59:00 by devjorginho       #+#    #+#             */
/*   Updated: 2025/12/04 21:16:35 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int is_simulation_finished(t_simulation *sim)
{
    int result;

    pthread_mutex_lock(&sim->simulation_lock);
    result = sim->end_simulation;
    pthread_mutex_unlock(&sim->simulation_lock);
    return (result);
}

int check_death(t_philo *philo, t_simulation *sim)
{
    long long time_since_last_meal;
    long long current_time;

    pthread_mutex_lock(&sim->simulation_lock);
    current_time = get_simulation_time_ms(sim);
    time_since_last_meal = current_time - philo->last_meal_time;
    if (time_since_last_meal > sim->time_to_die)
    {
        sim->end_simulation = 1;
        pthread_mutex_unlock(&sim->simulation_lock);
        pthread_mutex_lock(&sim->print_lock);
        printf("%llu %d died\n", current_time, philo->id);
        pthread_mutex_unlock(&sim->print_lock);
        return (1);
    }
    pthread_mutex_unlock(&sim->simulation_lock);
    return (0);
}
void *philo_routine(void *arg)
{
    t_philo *philo;
    t_simulation *sim;

    philo = (t_philo *)arg;
    sim = philo->sim;
    pthread_mutex_lock(&sim->simulation_lock);
    philo->last_meal_time = get_simulation_time_ms(sim);
    pthread_mutex_unlock(&sim->simulation_lock);
    if (philo->id % 2 == 0)
        ft_usleep(sim->time_to_eat / 2);
    while (!is_simulation_finished(sim))
    {
        philo_eat(philo);
        pthread_mutex_lock(&sim->simulation_lock);
        if (sim->limit_meals != -1 && philo->meals_count >= sim->limit_meals)
        {
            pthread_mutex_unlock(&sim->simulation_lock);
            break;
        }
        pthread_mutex_unlock(&sim->simulation_lock);
        philo_sleep(philo);
        philo_think(philo);
    }
    return (NULL);
}
void *routine_supervisor(void *arg)
{
    t_simulation *sim;
    int all_meals_done;
    int i;

    sim = (t_simulation *)arg;
    while (!is_simulation_finished(sim))
    {
        all_meals_done = 1;
        i = 0;
        while (i < sim->nbr_philo)
        {
            if (check_death(&sim->philosopher[i], sim))
                return (NULL);
            if (sim->limit_meals != -1)
            {
                pthread_mutex_lock(&sim->simulation_lock);
                if (sim->philosopher[i].meals_count < sim->limit_meals)
                    all_meals_done = 0;
                pthread_mutex_unlock(&sim->simulation_lock);
            }
            i++;
        }
        if (sim->limit_meals != -1 && all_meals_done)
        {
            pthread_mutex_lock(&sim->simulation_lock);
            sim->end_simulation = 1;
            pthread_mutex_unlock(&sim->simulation_lock);
            return (NULL);
        }
        usleep(500); 
    }
    return (NULL);
}