/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:38:36 by jde-carv          #+#    #+#             */
/*   Updated: 2025/12/03 17:57:18 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"


static int	current_time(void)
{
	struct timeval tv;
	int ret;

	if (gettimeofday(&tv, NULL) != 0)
		return NULL;
	ret = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ret);
}
static void	ft_think(t_simulation *sim) 
{
	pthread_mutex_lock(&sim->print_lock);
	printf("%lld %d is thinking", current_time(), &sim->philosopher->id);
	pthread_mutex_unlock(&sim->print_lock);
}

static void	ft_eat(t_simulation *sim) 
{

}

static void	ft_sleep(t_simulation *sim) 
{
	pthread_mutex_lock(&sim->print_lock);
	printf("%lld %d is sleeping", current_time(), &sim->philosopher->id);
	pthread_mutex_unlock(&sim->print_lock);
}