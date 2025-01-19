/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:49:42 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/17 18:13:01 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int check_status(t_philo *philo)
{
    pthread_mutex_lock(&philo->common_data->death_mutex);
        if (!philo->common_data->program_status)
        {
            pthread_mutex_unlock(&philo->common_data->death_mutex);
            return (0);
        }
        pthread_mutex_unlock(&philo->common_data->death_mutex);
    return (1);
}

// a monitoring, detached thread for a all philos
// checks for death and TODO: tracks the eat counter
void *watchdog_thread(void *arg)
{
    t_philo **philo_arr = (t_philo **)arg;
    long time_in_ms;
    int i;

    while (1)
    {
        for (i = 0; i < philo_arr[0]->common_data->no_philo; i++)
        {
            pthread_mutex_lock(&philo_arr[0]->common_data->death_mutex);
            get_time_in_ms(&philo_arr[0]->common_data->start_time, &time_in_ms);
            if (philo_arr[0]->common_data->program_status &&
                (time_in_ms - philo_arr[i]->last_meal > philo_arr[i]->common_data->time_to_die))
            {
                philo_arr[0]->common_data->program_status = false;
                philo_arr[i]->is_dead = true;
                printf("\033[0;32m%ldms\033[0m \033[0;31m%d died\033[0m\n", time_in_ms, philo_arr[i]->id);
                pthread_mutex_unlock(&philo_arr[0]->common_data->death_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(&philo_arr[0]->common_data->death_mutex);
        }
    }
    return (NULL);
}



