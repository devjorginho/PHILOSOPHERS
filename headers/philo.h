/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:36:34 by devjorginho       #+#    #+#             */
/*   Updated: 2025/12/06 20:06:55 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_simulation	t_simulation;

typedef struct s_philo
{
	int						id;
	pthread_t				thread_id;
	long long				last_meal_time;
	int						meals_count;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	t_simulation			*sim;
}							t_philo;

typedef struct s_simulation
{
	int						nbr_philo;
	long long				time_to_die;
	long long				time_to_eat;
	long long				time_to_sleep;
	int						limit_meals;
	pthread_mutex_t			*forks;
	long long				start_simulation;
	int						end_simulation;
	pthread_mutex_t			print_lock;
	pthread_mutex_t			simulation_lock;
	pthread_t				monitor_thread;
	t_philo					*philosopher;
}							t_simulation;

// VALIDATE_ARGUMENTS
int							validate_arguments(int ac, char **av);

// CLEAN FUNCTIONS
void						clean_simulation(t_simulation *sim);

// UTILS
void						ft_bzero(void *s, size_t n);
long						ft_atol(const char *s);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
void						*ft_calloc(size_t nmemb, size_t size);
int							has_philo(char *av);
long long					get_actual_time_ms(void);
long long					get_simulation_time_ms(t_simulation *sim);
void						ft_usleep(long long time_ms);
void						print_actions(t_philo *philo, char *status_msg);

// ROUTINE MANAGEMENT
int							init_mutexes(t_simulation *sim);
int							init_philos(t_simulation *sim);
t_simulation				*init_simulation(char **av);
void						*philo_routine(void *arg);
int							is_simulation_finished(t_simulation *sim);
int							check_death(t_philo *philo, t_simulation *sim);
void						*routine_supervisor(void *arg);
void						has_one_philo(t_simulation *sim, t_philo *philo);
// CHECK SIMULATION STATE
int							is_simulation_finished(t_simulation *sim);
int							check_death(t_philo *philo, t_simulation *sim);

// THREAD MANAGEMENT
void						join_all_threads(t_simulation *sim);
int							start_threads(t_simulation *sim);
t_simulation				*start_simulation(char **av);

// PRINT ACTIONS
void						print_actions(t_philo *philo, char *status_msg);
void						philo_sleep(t_philo *philo);
void						philo_think(t_philo *philo);
void						philo_eat(t_philo *philo);

#endif