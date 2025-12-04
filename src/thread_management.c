/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 21:00:32 by devjorginho       #+#    #+#             */
/*   Updated: 2025/12/04 21:11:16 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int is_one_philo(t_simulation *sim)
{
    sim->start_simulation = get_actual_time_ms(); 
    printf("0 1 has taken a fork\n");
    ft_usleep(sim->time_to_die);
    printf("%llu 1 died\n", (long long)sim->time_to_die);
    sim->end_simulation = 1; 
    return (1);
}

void join_all_threads(t_simulation *sim)
{
    int i;
    
    i = 0;
    if (sim->nbr_philo == 1)
        return;
    pthread_join(sim->monitor_thread, NULL);
    while (i < sim->nbr_philo)
    {
        pthread_join(sim->philosopher[i].thread_id, NULL);
        i++;
    }
}

t_simulation *start_simulation(char **av)
{
    t_simulation *sim;

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

int start_threads(t_simulation *sim)
{
    int i;
    
    if (sim->nbr_philo == 1)
        return (is_one_philo(sim));
    sim->start_simulation = get_actual_time_ms();
    i = 0;
    while (i < sim->nbr_philo)
    {
        if (pthread_create(&sim->philosopher[i].thread_id, NULL, 
                           &philo_routine, &sim->philosopher[i]) != 0)
        {
            sim->end_simulation = 1; 
            return (0);
        }
        i++;
    }
    if (pthread_create(&sim->monitor_thread, NULL, &routine_supervisor, sim) != 0)
    {
        sim->end_simulation = 1;
        return (0);
    }
    return (1);
}