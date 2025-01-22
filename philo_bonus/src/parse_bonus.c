/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:38:15 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/22 17:11:42 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static int	init_opt_arg(int ac, char **av, long temp, t_common_data *params)
{
	if (ac == 6)
	{
		if (!av[5] || ft_atol(av[5], &temp) || temp < 0 || temp > INT_MAX)
			return (1);
		params->no_must_eat = (int)temp;
		params->is_opt_arg = true;
	}
	return (0);
}

int	parse_args(int ac, char **av, t_common_data *params)
{
	long	temp;

	if (ac != 5 && ac != 6)
		return (1);
	if (!av[1] || ft_atol(av[1], &temp) || temp <= 0 || temp > INT_MAX)
		return (1);
	params->no_philo = (int)temp;
	if (!av[2] || ft_atol(av[2], &temp) || temp <= 0 || temp > LONG_MAX)
		return (1);
	params->time_to_die = temp;
	if (!av[3] || ft_atol(av[3], &temp) || temp <= 0 || temp > LONG_MAX)
		return (1);
	params->time_to_eat = temp;
	if (!av[4] || ft_atol(av[4], &temp) || temp <= 0 || temp > LONG_MAX)
		return (1);
	params->time_to_sleep = temp;
	gettimeofday(&params->start_time, NULL);
	params->is_opt_arg = false;
	params->program_status = true;
	return (init_opt_arg(ac, av, temp, params));
}

int	print_error(void)
{
	printf("valid exec:./philo <no. philosophers> <time to die>");
	printf("<time to eat> <time to sleep> [opt. <no. of times to eat>]\n");
	return (1);
}
