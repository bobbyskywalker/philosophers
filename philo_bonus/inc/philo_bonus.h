/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:50:05 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/24 14:45:11 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>

typedef struct s_philo
{
	int						id;
	int						eat_counter;
	bool					is_dead;
	long					last_meal;
	struct s_common_data	*common_data;
}							t_philo;

typedef struct s_common_data
{
	int						no_philo;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	int						no_must_eat;
	struct timeval			start_time;
	bool					program_status;
	bool					is_opt_arg;
	sem_t					*forks_sem;
	sem_t					*end_sem;
}							t_common_data;

// SECTION: parsing utils
int							parse_args(int ac, char **av,
								t_common_data *params);
int							print_error(void);

// SECTION: philo utils
int							ft_atol(const char *str, long *result);
void						ft_arr2d_free(t_philo **arr);
void						get_time_in_ms(struct timeval *start_time,
								long *ms);
int							ft_usleep(size_t milliseconds);
size_t						ft_usleep_gettime(void);

// SECTION: philo inits
pthread_t					*init_processes(t_common_data *data,
								t_philo **philo_arr);
t_philo						**init_philo(t_common_data *data);

// SECTION: philo routines
void						sim_sleeping(t_philo *arg);
void						sim_eating(t_philo *philo);
void						sim_thinking(t_philo *philo);
void						*philo_routine(void *arg);

// SECTION: cleanup
void						clean_up(t_common_data *data, pthread_t *threads,
								t_philo **philo_arr);

#endif
