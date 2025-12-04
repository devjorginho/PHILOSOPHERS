/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:42:37 by devjorginho       #+#    #+#             */
/*   Updated: 2025/12/04 20:42:38 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/philo.h"

// Função principal de impressão
void print_actions(t_philo *philo, char *status_msg)
{
    long long time;
    t_simulation *sim;

    sim = philo->sim;
    
    pthread_mutex_lock(&sim->print_lock);
    if (sim->end_simulation == 0)
    {
        // CORRIGIDO: Chama a função corretamente nomeada
        time = get_simulation_time_ms(sim);
        printf("%llu %d %s\n", time, philo->id, status_msg);
    }
    pthread_mutex_unlock(&sim->print_lock);
}

// Ação de Dormir
void philo_sleep(t_philo *philo)
{
    // CORRIGIDO: Chama 'print_actions'
    print_actions(philo, "is sleeping");
    ft_usleep(philo->sim->time_to_sleep); 
}

// Ação de Pensar
void philo_think(t_philo *philo)
{
    // CORRIGIDO: Chama 'print_actions'
    print_actions(philo, "is thinking");
}

// Ação de Comer (O bloco central da simulação)
void philo_eat(t_philo *philo)
{
    t_simulation *sim;

    sim = philo->sim;
    
    // 1. Pegar Garfos (Ordem para evitar deadlock: Left, then Right)
    pthread_mutex_lock(philo->left_fork);
    print_actions(philo, "has taken a fork");

    pthread_mutex_lock(philo->right_fork);
    print_actions(philo, "has taken a fork");
    
    // 2. Comer
    print_actions(philo, "is eating");
    
    // Atualiza o tempo da última refeição e o contador de refeições (Acesso Protegido)
    pthread_mutex_lock(&sim->simulation_lock);
    // CORRIGIDO: Chama a função corretamente nomeada
    philo->last_meal_time = get_simulation_time_ms(sim);
    philo->meals_count++;
    pthread_mutex_unlock(&sim->simulation_lock);
    
    ft_usleep(sim->time_to_eat);
    
    // 3. Soltar Garfos (Ordem inversa da que pegou: Right, then Left)
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}