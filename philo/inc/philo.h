#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

typedef struct s_philo
{
    int  no_philo;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int no_must_eat;
} t_philo;

int error_handler(int ac, char **av, t_philo *ph);
int	ft_atol(const char *str, long *result);

#endif
