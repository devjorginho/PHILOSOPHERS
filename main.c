/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:36:28 by devjorginho       #+#    #+#             */
/*   Updated: 2025/12/06 10:22:26 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

int main(int ac, char **av)
{
    t_simulation *sim;
    
    if(!validate_arguments(ac, av))
        return (1);
    sim = start_simulation(av);
    if (!sim)
        return (1);
    join_all_threads(sim); 
    clean_simulation(sim);
    return (0);
}
