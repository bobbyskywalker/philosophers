#include "../inc/philo.h"


// TODO: create structures with philosopher data (status, etc.)
// Create logging (activities)
// Initialize threads

void create_threads(t_philo *philo, int *n)
{
    int i;

    i = 0;
    while (i < philo->no_philo)
    {
        pthread_create(&philo->thread_list[i], NULL, dummy_philo_action, &n);
        i++;
    }
    i = 0;
    while (i < philo->no_philo)
    {
        pthread_join(philo->thread_list[i], NULL);
        i++;
    }
}

int main(int ac, char **av)
{
    t_philo *philo;

    int tmp = 1;
    philo = malloc(sizeof(t_philo));
    if (!philo)
        return (1);
    if (error_handler(ac, av, philo))
    {
        printf("valid exec: ./philo <no. philosophers> <time to die> <time to eat> <time to sleep> [opt. <no. of times to eat>]\n");
        return (1);
    }
    // philo->mutex = malloc(sizeof(pthread_mutex_t));
    // if (!philo->mutex)
    // {
    //     free(philo);
    //     return (1);
    // }

    // pthread_mutex_init(philo->mutex, NULL);

    // philo->thread_list = malloc(philo->no_philo * sizeof(pthread_t));
    // if (!philo->thread_list)
    // {
    //   free(philo);
    //   return (1);
    // }


    // create_threads(philo, &tmp);
    // pthread_mutex_destroy(philo->mutex);

    // free(philo->thread_list);
    // free(philo);
    // return (0);
}
