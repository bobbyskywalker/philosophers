/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:46:51 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/21 11:49:40 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	lock_left_fork(t_philo *philo, long time_in_ms)
{
	pthread_mutex_lock(&philo->common_data->forks_mutexes[philo->left_fork]);
	if (!check_status(philo))
	{
		pthread_mutex_unlock(
			&philo->common_data->forks_mutexes[philo->left_fork]);
		pthread_mutex_unlock(
			&philo->common_data->forks_mutexes[philo->right_fork]);
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
		pthread_mutex_unlock(
			&philo->common_data->forks_mutexes[philo->right_fork]);
		pthread_mutex_unlock(
			&philo->common_data->forks_mutexes[philo->left_fork]);
		return ;
	}
	get_time_in_ms(&philo->common_data->start_time, &time_in_ms);
	printf("\033[0;32m%ld\033[0m \033[0;35m%d has taken a fork\033[0m\n",
		time_in_ms, philo->id);
}

void	lock_forks(t_philo *philo, long time_in_ms)
{
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
}
