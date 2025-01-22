/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:39:40 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/22 15:48:21 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	main(int ac, char **av)
{
	t_common_data	*common_data;
	t_philo			**philo_arr;

	common_data = malloc(sizeof(t_common_data));
	if (!common_data)
		return (1);
	if (parse_args(ac, av, common_data))
		return (print_error());
	philo_arr = init_philo(common_data);
	if (init_processes(common_data, philo_arr))
		return (1);
	sem_close(common_data->forks_sem);
	return (0);
}
