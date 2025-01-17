/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:49:46 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/17 17:15:26 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void sim_thinking(t_philo *philo)
{
    long time_in_ms;

    get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
    printf("\033[0;32m%ldms\033[0m %d is thinking\n", time_in_ms, philo->id);
}

void sim_sleeping(t_philo *philo)
{
    long time_in_ms;

    usleep(philo->common_data->time_to_sleep * 1000);
    get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
    printf("\033[0;32m%ldms\033[0m %d is sleeping\n", time_in_ms, philo->id);
}

void sim_eating(t_philo *philo)
{
    long time_in_ms;

    pthread_mutex_lock(&philo->common_data->forks_mutexes[philo->left_fork]);
    get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
    printf("\033[0;32m%ldms\033[0m %d has taken a fork\n", time_in_ms, philo->id);
    pthread_mutex_lock(&philo->common_data->forks_mutexes[philo->right_fork]);
    get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
    printf("\033[0;32m%ldms\033[0m %d has taken a fork\n", time_in_ms, philo->id);
    get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
    printf("\033[0;32m%ldms\033[0m %d is eating\n", time_in_ms, philo->id);
    philo->eat_counter++;
    usleep(philo->common_data->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->common_data->forks_mutexes[philo->right_fork]);
    pthread_mutex_unlock(&philo->common_data->forks_mutexes[philo->left_fork]);
}

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (!philo->is_dead)
    {
        sim_thinking(philo);
        sim_eating(philo);
        sim_sleeping(philo);
    }
    return (NULL);
}


