/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:49:42 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/21 14:55:10 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->common_data->end_mutex);
	if (!(philo->common_data->program_status))
	{
		pthread_mutex_unlock(&philo->common_data->end_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->common_data->end_mutex);
	return (1);
}

void	update_after_death(t_philo **philo_arr, int i, long time_in_ms)
{
	philo_arr[0]->common_data->program_status = false;
	philo_arr[i]->is_dead = true;
	printf("\033[0;32m%ld\033[0m \033[0;31m%d died\033[0m\n", time_in_ms,
		philo_arr[i]->id);
}

bool	check_if_all_ate(t_philo **philo_arr)
{
	int	i;
	int	already_ate;
	int	no_must_eat;

	i = 0;
	already_ate = 0;
	no_must_eat = philo_arr[0]->common_data->no_must_eat;
	if (philo_arr[0]->common_data->is_opt_arg)
	{
		while (i < philo_arr[0]->common_data->no_philo)
		{
			if (philo_arr[i]->eat_counter >= no_must_eat)
				already_ate++;
			if (already_ate == philo_arr[i]->common_data->no_philo)
				return (true);
			i++;
		}
	}
	return (false);
}

void	*watchdog_loop(t_philo **philo_arr, long time_in_ms, int i)
{
	while (1)
	{
		i = -1;
		while (++i < philo_arr[0]->common_data->no_philo)
		{
			pthread_mutex_lock(&philo_arr[0]->common_data->end_mutex);
			get_time_in_ms(&philo_arr[0]->common_data->start_time, &time_in_ms);
			if (philo_arr[0]->common_data->program_status
				&& (time_in_ms - philo_arr[i]->last_meal
					> philo_arr[i]->common_data->time_to_die))
			{
				update_after_death(philo_arr, i, time_in_ms);
				pthread_mutex_unlock(&philo_arr[0]->common_data->end_mutex);
				return (NULL);
			}
			if (check_if_all_ate(philo_arr))
			{
				philo_arr[0]->common_data->program_status = false;
				pthread_mutex_unlock(&philo_arr[0]->common_data->end_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&philo_arr[0]->common_data->end_mutex);
		}
	}
	return (NULL);
}

// a monitoring, detached thread for a all philos
// checks for death and TODO: tracks the eat counter
void	*watchdog_thread(void *arg)
{
	t_philo	**philo_arr;
	long	time_in_ms;
	int		i;

	i = 0;
	time_in_ms = 0;
	philo_arr = (t_philo **)arg;
	return (watchdog_loop(philo_arr, time_in_ms, i));
}
