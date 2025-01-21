/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:49:52 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/21 13:21:46 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// TODO: fix additional printing after all ate
int	main(int ac, char **av)
{
	t_common_data	*common_data;
	t_philo			**philo_arr;
	pthread_t		*threads;
	pthread_t		watchdog;

	threads = NULL;
	common_data = malloc(sizeof(t_common_data));
	if (!common_data)
		return (1);
	if (parse_args(ac, av, common_data))
		return (print_error());
	if (init_forks(common_data))
		return (1);
	philo_arr = init_philo(common_data);
	if (pthread_create(&watchdog, NULL, watchdog_thread, (void *)philo_arr))
		return (1);
	pthread_detach(watchdog);
	threads = init_threads(common_data, philo_arr);
	clean_up(common_data, threads, philo_arr);
	return (0);
}
