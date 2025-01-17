/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:49:46 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/17 16:51:37 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	sim_thinking(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("%ldms %d is thinking\n", tv.tv_sec * 1000 + tv.tv_usec / 1000,
		philo->id);
}

void	sim_sleeping(t_philo *philo)
{
	struct timeval	tv;

	usleep(philo->common_data->time_to_sleep * 1000);
	gettimeofday(&tv, NULL);
	printf("%ldms %d is sleeping\n", tv.tv_sec * 1000 + tv.tv_usec / 1000,
		philo->id);
}

void	sim_eating(t_philo *philo)
{
	struct timeval	tv;

	pthread_mutex_lock(&philo->common_data->forks_mutexes[philo->left_fork]);
	gettimeofday(&tv, NULL);
	printf("%ldms %d has taken a fork\n", tv.tv_sec * 1000 + tv.tv_usec / 1000,
		philo->id);
	pthread_mutex_lock(&philo->common_data->forks_mutexes[philo->right_fork]);
	gettimeofday(&tv, NULL);
	printf("%ldms %d has taken a fork\n", tv.tv_sec * 1000 + tv.tv_usec / 1000,
		philo->id);
	gettimeofday(&tv, NULL);
	printf("%ldms %d is eating\n", tv.tv_sec * 1000 + tv.tv_usec / 1000,
		philo->id);
	philo->eat_counter++;
	usleep(philo->common_data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->common_data->forks_mutexes[philo->right_fork]);
	pthread_mutex_unlock(&philo->common_data->forks_mutexes[philo->left_fork]);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->is_dead)
	{
		sim_thinking(philo);
		sim_eating(philo);
		sim_sleeping(philo);
	}
	return (NULL);
}
