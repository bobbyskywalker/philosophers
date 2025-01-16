#include "../inc/philo.h"

void *dummy_philo_action(void *n)
{
    pthread_mutex_lock(&mutex);

    n += 30;

    pthread_mutex_unlock(&mutex);
    return NULL;
}

void create_threads(t_philo *philo, int n)
{
    size_t i;

    i = 0;
    while (i < philo->no_philo)
    {
        pthread_create(&philo->thread_list[i], NULL, dummy_philo_action, &n);
        i++;
    }
    while (i < philo->no_philo)
    {
        pthread_join(philo->thread_list[i], NULL);
        i++;
    }
}

int main(int ac, char **av)
{
    t_philo *philo;
    pthread_mutex_t mutex;

    int tmp = 1;
    philo = malloc(sizeof(t_philo));
    if (!philo)
        return (1);
    if (error_handler(ac, av, philo))
    {
        printf("valid exec: ./philo <no. philosophers> <time to die> <time to eat> <time to sleep> [opt. <no. of times to eat>]\n");
        return (1);
    }
    philo->thread_list = malloc(philo->no_philo * sizeof(pthread_t));
    if (!philo->thread_list)
    {
      free(philo);
      return (1);
    }

    pthread_mutex_init(&mutex, NULL);
    create_threads(philo, tmp);
    pthread_mutex_destroy(&mutex);

    printf("%d", tmp);
    // printf("no philo: %d\n", philo->no_philo);
    // printf("ttd: %lu\n", philo->time_to_die);
    // printf("tte: %lu\n", philo->time_to_eat);
    // printf("tts: %lu\n", philo->time_to_sleep);
    // printf("ttd: %lu\n", philo->time_to_die);
    // printf("opt: %d\n", philo->no_must_eat);
    free(philo->thread_list);
    free(philo);
    return (0);
}
