/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:49:46 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/20 19:08:15 by agarbacz         ###   ########.fr       */
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

void	lock_left_fork(t_philo *philo, long time_in_ms)
{
	pthread_mutex_lock(&philo->common_data->forks_mutexes[philo->left_fork]);
	if (!check_status(philo))
	{
		pthread_mutex_unlock(&philo->common_data->forks_mutexes[philo->left_fork]);
		pthread_mutex_unlock(&philo->common_data->forks_mutexes[philo->right_fork]);
		return ;
	}
	get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
	printf("\033[0;32m%ld\033[0m \033[0;35m%d has taken a fork\033[0m\n",
		time_in_ms, philo->id);
}

void	lock_right_fork(t_philo *philo, long time_in_ms)
{
	pthread_mutex_lock(&philo->common_data->forks_mutexes[philo->right_fork]);
	if (!check_status(philo))
	{
		pthread_mutex_unlock(&philo->common_data->forks_mutexes[philo->right_fork]);
		pthread_mutex_unlock(&philo->common_data->forks_mutexes[philo->left_fork]);
		return ;
	}
	get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
	printf("\033[0;32m%ld\033[0m \033[0;35m%d has taken a fork\033[0m\n",
		time_in_ms, philo->id);
}

void	sim_eating(t_philo *philo)
{
	long	time_in_ms;

	time_in_ms = 0;
	if (!check_status(philo))
		return ;
	if (philo->common_data->no_philo % 2 == 0)
	{
		lock_left_fork(philo, time_in_ms);
		lock_right_fork(philo, time_in_ms);
	}
	else
	{
		lock_right_fork(philo, time_in_ms);
		lock_left_fork(philo, time_in_ms);
	}
	pthread_mutex_lock(&philo->common_data->death_mutex);
	if (philo->common_data->program_status)
	{
		get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
		philo->last_meal = time_in_ms;
		printf("\033[0;32m%ld\033[0m %d is eating\n", time_in_ms, philo->id);
		philo->eat_counter++;
	}
	pthread_mutex_unlock(&philo->common_data->death_mutex);
	ft_usleep(philo->common_data->time_to_eat);
	pthread_mutex_unlock(&philo->common_data->forks_mutexes[philo->right_fork]);
	pthread_mutex_unlock(&philo->common_data->forks_mutexes[philo->left_fork]);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!(philo->id % 2))
		ft_usleep(1);
	while (philo->common_data->program_status && !(philo->is_dead))
	{
		if (!check_status(philo) || philo->is_dead
			|| philo->common_data->program_status == false)
			return (NULL);
		sim_eating(philo);
		if (!check_status(philo) || philo->is_dead
			|| philo->common_data->program_status == false)
			return (NULL);
		sim_sleeping(philo);
		if (!check_status(philo) || philo->is_dead
			|| philo->common_data->program_status == false)
			return (NULL);
		sim_thinking(philo);
		ft_usleep(10);
	}
	return (NULL);
}
