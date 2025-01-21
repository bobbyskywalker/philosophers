/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:49:46 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/21 15:38:33 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	sim_thinking(t_philo *philo)
{
	long	time_in_ms;

	if (!check_status(philo))
		return ;
	get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
	printf("\033[0;32m%ld\033[0m %d is thinking\n", time_in_ms, philo->id);
}

void	sim_sleeping(t_philo *philo)
{
	long	time_in_ms;

	if (!check_status(philo))
		return ;
	get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
	printf("\033[0;32m%ld\033[0m %d is sleeping\n", time_in_ms, philo->id);
	ft_usleep(philo->common_data->time_to_sleep);
}

void	sim_eating(t_philo *philo)
{
	long	time;

	time = 0;
	if (!check_status(philo))
		return ;
	if (philo->common_data->no_philo == 1)
	{
		lock_left_fork(philo, time);
		pthread_mutex_unlock(&philo->common_data->forks_mutexes[philo->l_fork]);
	}
	else
	{
		lock_forks(philo, time);
		pthread_mutex_lock(&philo->common_data->end_mutex);
		if (philo->common_data->program_status)
		{
			get_time_in_ms(&philo->common_data->start_time, &time);
			philo->last_meal = time;
			printf("\033[0;32m%ld\033[0m %d is eating\n", time, philo->id);
			philo->eat_counter++;
		}
		pthread_mutex_unlock(&philo->common_data->end_mutex);
		ft_usleep(philo->common_data->time_to_eat);
		unlock_forks(philo);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!(philo->id % 2))
		ft_usleep(1);
	while (1)
	{
		if (!check_status(philo) || philo->is_dead)
			return (NULL);
		sim_eating(philo);
		if (!check_status(philo) || philo->is_dead)
			return (NULL);
		sim_sleeping(philo);
		if (!check_status(philo) || philo->is_dead)
			return (NULL);
		sim_thinking(philo);
		ft_usleep(1);
	}
	return (NULL);
}
