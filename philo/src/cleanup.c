/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:42:43 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/17 15:42:54 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	destroy_forks(t_common_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_philo)
		pthread_mutex_destroy(&data->forks_mutexes[i++]);
}