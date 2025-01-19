/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:23:11 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/17 18:08:08 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	**init_philo(t_common_data *data)
{
	int		i;
	t_philo	**philo_arr;

	i = 0;
	philo_arr = malloc(data->no_philo * sizeof(t_philo *));
	if (!philo_arr)
		return (NULL);
	while (i < data->no_philo)
	{
		philo_arr[i] = malloc(sizeof(t_philo));
		if (!philo_arr[i])
		{
			ft_arr2d_free(philo_arr);
			return (NULL);
		}
		philo_arr[i]->left_fork = i;
		philo_arr[i]->right_fork = (i + 1) % data->no_philo;
		philo_arr[i]->id = i + 1;
		philo_arr[i]->eat_counter = 0;
		philo_arr[i]->is_dead = false;
		philo_arr[i]->common_data = data;
		i++;
	}
	return (philo_arr);
}

pthread_t	*init_threads(pthread_t *threads, t_common_data *data,
		t_philo **philo_arr)
{
	int	i; 

	threads = malloc(sizeof(pthread_t) * data->no_philo);
	if (!threads)
		return (NULL);
	i = 0;
	while (i < data->no_philo)
	{
		if (pthread_create(&threads[i], NULL, philo_routine,
				(void *)philo_arr[i]))
			return (NULL);
		i++;
	}
	i = 0;
	while (i < data->no_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (threads);
}

// no_philo == no_forks de facto means no_mutexes
int	init_forks(t_common_data *data)
{
	int	i;

	data->forks_mutexes = malloc(sizeof(pthread_mutex_t) * data->no_philo);
	if (!data->forks_mutexes)
		return (1);
	data->program_status = true;
	i = 0;
	while (i < data->no_philo)
	{
		if (pthread_mutex_init(&data->forks_mutexes[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->death_mutex, NULL))
        return (1);
	return (0);
}
