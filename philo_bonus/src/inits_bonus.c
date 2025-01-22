/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:23:11 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/22 17:22:26 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	init_forks(t_common_data *data)
{
	sem_unlink("/forks_semaphore");
	sem_unlink("/end_semaphore");
	data->forks_sem = sem_open("/forks_semaphore", O_CREAT, 0600,
			data->no_philo);
	if (data->forks_sem == SEM_FAILED)
		return (-1);
	data->end_sem = sem_open("/end_semaphore", O_CREAT, 0600, 1);
	if (data->end_sem == SEM_FAILED)
		return (-1);
	return (0);
}

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
		philo_arr[i]->id = i + 1;
		philo_arr[i]->eat_counter = 0;
		philo_arr[i]->is_dead = false;
		philo_arr[i]->last_meal = 0;
		philo_arr[i]->common_data = data;
		init_forks(philo_arr[i]->common_data);
		i++;
	}
	return (philo_arr);
}

pthread_t	*init_processes(t_common_data *data, t_philo **philo_arr)
{
	pid_t	pid;
	int		i;
	int		status;
	pid_t	*pids;

	pids = malloc(data->no_philo * sizeof(pid_t));
	if (!pids)
		return (NULL);
	i = -1;
	while (++i < data->no_philo)
	{
		pid = fork();
		if (pid == -1)
		{
			free(pids);
			ft_arr2d_free(philo_arr);
			return (NULL);
		}
		else if (pid == 0)
		{
			philo_routine(philo_arr[i]);
			exit(0);
		}
		else
			pids[i] = pid;
	}
	i = -1;
	while (++i < data->no_philo)
		waitpid(pids[i], &status, 0);
	free(pids);
	return (NULL);
}
