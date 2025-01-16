#include "../inc/philo.h"


void *add(void *value)
{
      printf("%d\n", (*(int *)value) + 1);
      return NULL;
}


int main(int ac, char **av)
{
    t_philo *philo;

    error_handler(ac, av, philo);
    printf("no philo: %d\n", philo->no_philo);
    printf("ttd: %lu\n", philo->time_to_die);
    printf("tte: %lu\n", philo->time_to_eat);
    printf("tts: %lu\n", philo->time_to_sleep);
//    printf("ttd: %lu", philo.time_to_die);
    return (0);
}
