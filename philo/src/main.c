#include "../inc/philo.h"


void *add(void *value)
{
      printf("%d\n", (*(int *)value) + 1);
      return NULL;
}


int main(int ac, char **av)
{
    t_philo *philo;

    philo = malloc(sizeof(t_philo));
    if (!philo)
        return (1);
    if (error_handler(ac, av, philo))
    {
        printf("valid exec: ./philo <no. philosophers> <time to die> <time to eat> <time to sleep> [opt. <no. of times to eat>]\n");
        return (1);
    }
    // printf("no philo: %d\n", philo->no_philo);
    // printf("ttd: %lu\n", philo->time_to_die);
    // printf("tte: %lu\n", philo->time_to_eat);
    // printf("tts: %lu\n", philo->time_to_sleep);
    // printf("ttd: %lu\n", philo->time_to_die);
    // printf("opt: %d\n", philo->no_must_eat);
    return (0);
}
