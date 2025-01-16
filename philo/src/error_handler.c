#include "../inc/philo.h"
#include <limits.h> // For INT_MAX and LONG_MAX

int error_handler(int ac, char **av, t_philo *philo)
{
    long temp;

    if (ac != 5 && ac != 6)
        return (1);
    if (ft_atol(av[1], &temp) || temp <= 0 || temp > INT_MAX)
        return (1);
    philo->no_philo = (int)temp;
    if (ft_atol(av[2], &temp) || temp <= 0 || temp > LONG_MAX)
        return (1);
    philo->time_to_die = temp;
    if (ft_atol(av[3], &temp) || temp <= 0 || temp > LONG_MAX)
        return (1);
    philo->time_to_eat = temp;
    if (ft_atol(av[4], &temp) || temp <= 0 || temp > LONG_MAX)
        return (1);
    philo->time_to_sleep = temp;
    if (ac == 6)
    {
        if (ft_atol(av[5], &temp) || temp < 0 || temp > INT_MAX)
            return (1);
        philo->no_must_eat = (int)temp;
    }

    return (0); // Success
}
