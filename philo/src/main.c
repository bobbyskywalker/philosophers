/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:49:52 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/17 15:58:50 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_common_data	*common_data;
	t_philo			**philo_arr;
	pthread_t		*threads;

	threads = NULL;
	common_data = malloc(sizeof(t_common_data));
	if (!common_data)
		return (1);
	if (parse_args(ac, av, common_data))
		return (print_error());
	if (init_forks(common_data))
		return (1);
	philo_arr = init_philo(common_data);
	init_threads(threads, common_data, philo_arr);
	free(threads);
	destroy_forks(common_data);
	return (0);
}
