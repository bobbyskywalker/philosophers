/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:42:43 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/21 13:06:44 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	destroy_mutexes(t_common_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->end_mutex);
	while (i < data->no_philo)
		pthread_mutex_destroy(&data->forks_mutexes[i++]);
	free(data->forks_mutexes);
}

void	clean_up(t_common_data *data, pthread_t *threads, t_philo **philo_arr)
{
	if (threads)
	{
		free(threads);
		threads = NULL;
	}
	if (philo_arr)
		ft_arr2d_free(philo_arr);
	destroy_mutexes(data);
	if (data)
	{
		free(data);
	}
}
