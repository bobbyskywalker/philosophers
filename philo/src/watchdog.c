/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:49:42 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/24 14:28:32 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// a utility function to that checks the status of a program 
// before a philo performs any action
int	check_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->sh_data->end_mutex);
	if (!(philo->sh_data->run_flag))
	{
		pthread_mutex_unlock(&philo->sh_data->end_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->sh_data->end_mutex);
	return (1);
}

void	update_after_death(t_philo **philo_arr, int i, long time_in_ms)
{
	philo_arr[0]->sh_data->run_flag = false;
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
	no_must_eat = philo_arr[0]->sh_data->no_must_eat;
	if (philo_arr[0]->sh_data->is_opt_arg)
	{
		while (i < philo_arr[0]->sh_data->no_philo)
		{
			if (philo_arr[i]->eat_counter >= no_must_eat)
				already_ate++;
			if (already_ate == philo_arr[i]->sh_data->no_philo)
				return (true);
			i++;
		}
	}
	return (false);
}

void	*watchdog_loop(t_philo **ph_arr, long t_ms, int i)
{
	while (1)
	{
		i = -1;
		while (++i < ph_arr[0]->sh_data->no_philo)
		{
			pthread_mutex_lock(&ph_arr[0]->sh_data->end_mutex);
			get_time_in_ms(&ph_arr[0]->sh_data->start_time, &t_ms);
			if (ph_arr[0]->sh_data->run_flag && (t_ms - ph_arr[i]->last_meal
					> ph_arr[i]->sh_data->time_to_die))
			{
				update_after_death(ph_arr, i, t_ms);
				pthread_mutex_unlock(&ph_arr[0]->sh_data->end_mutex);
				return (NULL);
			}
			if (check_if_all_ate(ph_arr))
			{
				ph_arr[0]->sh_data->run_flag = false;
				pthread_mutex_unlock(&ph_arr[0]->sh_data->end_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&ph_arr[0]->sh_data->end_mutex);
			ft_usleep(1);
		}
	}
	return (NULL);
}

// a monitoring, detached thread for a all philos
// exits the program if a philo dies or all of them eat
// no_must_eat times
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
