/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:50:05 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/20 18:52:54 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	int						left_fork;
	int						right_fork;
	int						eat_counter;
	bool					is_dead;
	long					last_meal;
	pthread_mutex_t			mutex;
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
	pthread_mutex_t			*forks_mutexes;
	pthread_mutex_t			death_mutex;
	bool					program_status;
	bool					is_opt_arg;
}							t_common_data;

// SECTION: philo utils
int							parse_args(int ac, char **av,
								t_common_data *params);
int							print_error(void);
int							ft_atol(const char *str, long *result);
void						ft_arr2d_free(t_philo **arr);
void						get_time_in_ms(struct timeval *start_time,
								long *ms);
int							ft_usleep(size_t milliseconds);
size_t						ft_usleep_gettime(void);

// SECTION: philo inits
int							init_forks(t_common_data *data);
pthread_t					*init_threads(pthread_t *threads,
								t_common_data *data, t_philo **philo_arr);
t_philo						**init_philo(t_common_data *data);

// SECTION: philo routines
void						sim_sleeping(t_philo *arg);
void						sim_eating(t_philo *philo);
void						sim_thinking(t_philo *philo);
void						*philo_routine(void *arg);
int							ft_usleep(size_t milliseconds);

// SECTION: philo monitoring
void						*watchdog_thread(void *arg);
int							check_status(t_philo *philo);

// SECTION: cleanup
void						destroy_mutexes(t_common_data *data);

#endif
