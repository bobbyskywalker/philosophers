/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:38:46 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/22 14:03:50 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

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
	int	len;

	len = arr[0]->common_data->no_philo;
	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}
