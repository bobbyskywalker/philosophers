/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:46:51 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/21 15:26:33 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	lock_left_fork(t_philo *philo, long time_in_ms)
{
	pthread_mutex_lock(&philo->sh_data->forks_mutexes[philo->l_fork]);
	if (!check_status(philo))
	{
		pthread_mutex_unlock(
			&philo->sh_data->forks_mutexes[philo->l_fork]);
		if (philo->id % 2 != 0)
			pthread_mutex_unlock(&philo->sh_data->forks_mutexes[philo->r_fork]);
		return ;
	}
	get_time_in_ms(&philo->sh_data->start_time, &time_in_ms);
	printf("\033[0;32m%ld\033[0m \033[0;35m%d has taken a fork\033[0m\n",
		time_in_ms, philo->id);
}

void	lock_right_fork(t_philo *philo, long time_in_ms)
{
	pthread_mutex_lock(&philo->sh_data->forks_mutexes[philo->r_fork]);
	if (!check_status(philo))
	{
		pthread_mutex_unlock(
			&philo->sh_data->forks_mutexes[philo->r_fork]);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_unlock(
				&philo->sh_data->forks_mutexes[philo->l_fork]);
		}
		return ;
	}
	get_time_in_ms(&philo->sh_data->start_time, &time_in_ms);
	printf("\033[0;32m%ld\033[0m \033[0;35m%d has taken a fork\033[0m\n",
		time_in_ms, philo->id);
}

void	lock_forks(t_philo *philo, long time_in_ms)
{
	if (philo->sh_data->no_philo % 2 == 0)
	{
		lock_left_fork(philo, time_in_ms);
		lock_right_fork(philo, time_in_ms);
	}
	else
	{
		lock_right_fork(philo, time_in_ms);
		lock_left_fork(philo, time_in_ms);
	}
}

void	unlock_forks(t_philo *philo)
{
	if (philo->sh_data->no_philo % 2 == 0)
	{
		pthread_mutex_unlock(&philo->sh_data->forks_mutexes[philo->l_fork]);
		pthread_mutex_unlock(&philo->sh_data->forks_mutexes[philo->r_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->sh_data->forks_mutexes[philo->r_fork]);
		pthread_mutex_unlock(&philo->sh_data->forks_mutexes[philo->l_fork]);
	}
}
