/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:50:05 by agarbacz          #+#    #+#             */
/*   Updated: 2025/01/21 15:26:16 by agarbacz         ###   ########.fr       */
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
	int						l_fork;
	int						r_fork;
	int						eat_counter;
	bool					is_dead;
	long					last_meal;
	pthread_mutex_t			mutex;
	struct s_common_data	*sh_data;
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
	pthread_mutex_t			end_mutex;
	bool					run_flag;
	bool					is_opt_arg;
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
int							init_forks(t_common_data *data);
pthread_t					*init_threads(t_common_data *data,
								t_philo **philo_arr);
t_philo						**init_philo(t_common_data *data);

// SECTION: philo routines
void						sim_sleeping(t_philo *arg);
void						sim_eating(t_philo *philo);
void						sim_thinking(t_philo *philo);
void						lock_forks(t_philo *philo, long time_in_ms);
void						lock_left_fork(t_philo *philo, long time_in_ms);
void						lock_right_fork(t_philo *philo, long time_in_ms);
void						unlock_forks(t_philo *philo);
void						*philo_routine(void *arg);

// SECTION: philo monitoring
void						*watchdog_thread(void *arg);
int							check_status(t_philo *philo);

// SECTION: cleanup
void						clean_up(t_common_data *data, pthread_t *threads,
								t_philo **philo_arr);

#endif
