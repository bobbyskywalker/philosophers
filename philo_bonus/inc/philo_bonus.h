#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
    int						id;
    int						l_fork;
    int						r_fork;
    int						eat_counter;
    bool					is_dead;
    long					last_meal;
    pthread_mutex_t			mutex;
    struct s_common_data	*common_data;
}							t_philo;

#endif
