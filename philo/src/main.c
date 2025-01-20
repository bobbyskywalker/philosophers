/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:49:52 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/20 11:34:02 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


// TODO: add an eat counter to the watchdog
// modify the fork picking to treat BOTH forks as an atomic operation
// if you cant pick any of the forks dont pick none
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
	init_threads(threads, common_data, philo_arr);
	free(threads);
	destroy_mutexes(common_data);
	return (0);
}
