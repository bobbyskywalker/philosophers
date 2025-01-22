/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:46:51 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/22 17:23:34 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	sim_thinking(t_philo *philo)
{
	long	time_in_ms;

	get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
	printf("\033[0;32m%ld\033[0m %d is thinking\n", time_in_ms, philo->id);
}

void	sim_sleeping(t_philo *philo)
{
	long	time_in_ms;

	get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
	printf("\033[0;32m%ld\033[0m %d is sleeping\n", time_in_ms, philo->id);
	ft_usleep(philo->common_data->time_to_sleep);
}

void sim_eating(t_philo *philo)
{
    long time_in_ms;
    
    sem_wait(philo->common_data->forks_sem);
    get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
    printf("\033[0;32m%ld\033[0m \033[0;35m%d has taken a fork\033[0m\n",
        time_in_ms, philo->id);
    sem_wait(philo->common_data->forks_sem);
    get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
    printf("\033[0;32m%ld\033[0m \033[0;35m%d has taken a fork\033[0m\n",
        time_in_ms, philo->id);
    sem_wait(philo->common_data->end_sem);
    get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
	philo->last_meal = time_in_ms;
    printf("\033[0;32m%ld\033[0m %d is eating\n", time_in_ms, philo->id);
    sem_post(philo->common_data->end_sem);
    
    ft_usleep(philo->common_data->time_to_eat);
    sem_post(philo->common_data->forks_sem);
    sem_post(philo->common_data->forks_sem);
}

void *check_for_death(void *arg)
{
    t_philo *philo;
    long time_in_ms;
    
    philo = (t_philo *)arg;
    while (!philo->is_dead)
    {
        sem_wait(philo->common_data->end_sem);
        get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
        if (time_in_ms - philo->last_meal > philo->common_data->time_to_die)
        {
            printf("\033[0;31m%ld\033[0m %d died\n", time_in_ms, philo->id);
            philo->is_dead = true;
            philo->common_data->program_status = false;
            sem_post(philo->common_data->end_sem);
            break;
        }
        sem_post(philo->common_data->end_sem);
        usleep(10);
    }
    return (NULL);
}

void *philo_routine(void *arg)
{
    t_philo *philo;
    pthread_t death_monitor;
    long time_in_ms;
    
    philo = (t_philo *)arg;
    philo->is_dead = false;
    get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
    philo->last_meal = time_in_ms;
    
    if (pthread_create(&death_monitor, NULL, check_for_death, (void *)philo) != 0)
        return (NULL);
    if (!(philo->id % 2))
		ft_usleep(1);
    while (!philo->is_dead && philo->common_data->program_status)
    {
		if ((philo->common_data->program_status))
        	sim_eating(philo);
		if ((philo->common_data->program_status))
        	sim_sleeping(philo);
		if ((philo->common_data->program_status))
        	sim_thinking(philo);
    }
    pthread_join(death_monitor, NULL);
    return (NULL);
}