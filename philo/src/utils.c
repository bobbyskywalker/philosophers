/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:38:46 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/17 16:58:00 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atol(const char *str, long *result)
{
	long	num;
	int		sign;
	int		digit;

	num = 0;
	sign = 1;
	while (*str && ft_isspace((unsigned char)*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str && ft_isdigit((unsigned char)*str))
	{
		digit = *str - '0';
		if ((num > (LONG_MAX / 10)) || (num == (LONG_MAX / 10)
				&& digit > (LONG_MAX % 10)))
		{
			*result = 0;
			return (1);
		}
		num = num * 10 + digit;
		str++;
	}
	*result = num * sign;
	return (0);
}

void	ft_arr2d_free(t_philo **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	get_time_in_ms(struct timeval *start_time, long *ms)
{
	struct timeval tv;
	long seconds;
	long microseconds;

	gettimeofday(&tv, NULL);
	seconds = tv.tv_sec - start_time->tv_sec;
	microseconds = tv.tv_usec - start_time->tv_usec;
	*ms = (seconds * 1000) + (microseconds / 1000);
}