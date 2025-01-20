/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:49:46 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/20 12:11:30 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void sim_thinking(t_philo *philo)
{
    long time_in_ms;

    if (!check_status(philo))
        return;    
    get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
    printf("\033[0;32m%ldms\033[0m %d is thinking\n", time_in_ms, philo->id);
}

void sim_sleeping(t_philo *philo)
{
    long time_in_ms;

    if (!check_status(philo))
        return;
    get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
    printf("\033[0;32m%ldms\033[0m %d is sleeping\n", time_in_ms, philo->id);
    usleep(philo->common_data->time_to_sleep * 1000);
}

void sim_eating(t_philo *philo)
{
    long time_in_ms;

    if (!check_status(philo))
        return;
    pthread_mutex_lock(&philo->common_data->forks_mutexes[philo->left_fork]);
    if (!check_status(philo))
    {
        pthread_mutex_unlock(&philo->common_data->forks_mutexes[philo->left_fork]);
        return;
    }
    get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
    printf("\033[0;32m%ldms\033[0m \033[0;35m%d has taken a fork\033[0m\n", time_in_ms, philo->id);
    pthread_mutex_lock(&philo->common_data->forks_mutexes[philo->right_fork]);
    if (!check_status(philo))
    {
        pthread_mutex_unlock(&philo->common_data->forks_mutexes[philo->right_fork]);
        pthread_mutex_unlock(&philo->common_data->forks_mutexes[philo->left_fork]);
        return;
    }
    get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
    printf("\033[0;32m%ldms\033[0m \033[0;35m%d has taken a fork\033[0m\n", time_in_ms, philo->id);
    pthread_mutex_lock(&philo->common_data->death_mutex);
    if (philo->common_data->program_status)
    {
        get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
        philo->last_meal = time_in_ms;
        printf("\033[0;32m%ldms\033[0m %d is eating\n", time_in_ms, philo->id);
        philo->eat_counter++;
    }
    pthread_mutex_unlock(&philo->common_data->death_mutex);
    usleep(philo->common_data->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->common_data->forks_mutexes[philo->right_fork]);
    pthread_mutex_unlock(&philo->common_data->forks_mutexes[philo->left_fork]);
}

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (philo->common_data->program_status && !philo->is_dead)
    {
        if (!check_status(philo) || philo->is_dead)
            return (NULL);
        sim_thinking(philo);
        if (!check_status(philo) || philo->is_dead)
            return (NULL);
        sim_eating(philo);
        if (!check_status(philo) || philo->is_dead)
            return (NULL);
        sim_sleeping(philo);
    }
    return (NULL);
}



