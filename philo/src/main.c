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

int	main(int ac, char **av)
{
	t_common_data	*sh_data;
	t_philo			**philo_arr;
	pthread_t		*threads;
	pthread_t		watchdog;

	threads = NULL;
	sh_data = malloc(sizeof(t_common_data));
	if (!sh_data)
		return (1);
	if (parse_args(ac, av, sh_data))
		return (print_error());
	if (init_forks(sh_data))
		return (1);
	philo_arr = init_philo(sh_data);
	if (pthread_create(&watchdog, NULL, watchdog_thread, (void *)philo_arr))
		return (1);
	pthread_detach(watchdog);
	threads = init_threads(sh_data, philo_arr);
	clean_up(sh_data, threads, philo_arr);
	return (0);
}
