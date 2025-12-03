/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:36:28 by devjorginho       #+#    #+#             */
/*   Updated: 2025/11/29 20:07:34 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

int main(int ac, char **av)
{
	t_simulation *sim;
	
	if(!validate_arguments(ac, av))
		return (1);
	sim = new_simulation(av);
	if (!init_mutexes(sim))
		return (1);
}