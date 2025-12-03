/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:36:34 by devjorginho       #+#    #+#             */
/*   Updated: 2025/11/29 20:19:46 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_simulation
{
    int    			nbr_philo;
    uint64_t    	time_to_die;
    uint64_t    	time_to_eat;
    uint64_t    	time_to_sleep;
    int    			limit_meals;
	pthread_mutex_t *forks;
	uint64_t		start_simulation;
	int            	end_simulation;
    pthread_mutex_t print_lock;
    pthread_mutex_t simulation_lock;
} t_simulation;

typedef struct s_philo
{
    int             id;
    pthread_t       thread_id;
    uint64_t        last_meal_time;
    int             meals_count;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_simulation    *sim;
} t_philo;

// CHECK_ARGUMENTS
int	validate_arguments(int ac, char **av);

// UTILS
long	ft_atol(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// INIT_SMULATION
t_simulation *new_simulation(char **av);

#endif