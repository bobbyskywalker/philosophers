#include "../inc/philo.h"


void *add(void *value)
{
      printf("%d\n", (*(int *)value) + 1);
      return NULL;
}


int main(int argc, char **argv)
{
    pthread_t thread1;
    pthread_t thread2;

    long v = 300;
    long v2 = 600;
    pthread_create(&thread1, NULL, add, (void *) &v);
    pthread_create(&thread2, NULL, add, (void *) &v2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    add(&v);
    add(&v2);
    return (0);
}
