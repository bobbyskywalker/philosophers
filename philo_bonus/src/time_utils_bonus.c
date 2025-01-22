/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:04:50 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/22 15:48:42 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	get_time_in_ms(struct timeval *start_time, long *ms)
{
	struct timeval	tv;
	long			seconds;
	long			microseconds;

	gettimeofday(&tv, NULL);
	seconds = tv.tv_sec - start_time->tv_sec;
	microseconds = tv.tv_usec - start_time->tv_usec;
	*ms = (seconds * 1000) + (microseconds / 1000);
}

size_t	ft_usleep_gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = ft_usleep_gettime();
	while ((ft_usleep_gettime() - start) < milliseconds)
		usleep(500);
	return (0);
}
