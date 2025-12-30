/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:50:44 by leberton          #+#    #+#             */
/*   Updated: 2025/12/30 14:51:44 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "includes.h"

typedef enum e_error_code
{
	ERROR_NONE,
	ERROR_ARGC,
	ERROR_INVALID_ARG,
	ERROR_MEMORY,
	ERROR_THREAD,
	ERROR_MUTEX,
}				t_error_code;

typedef struct s_simulation_config
{
	int					philo_count;
	int					death_time_ms;
	int					eat_duration_ms;
	int					sleep_duration_ms;
	int					required_meal_count;
	long				sim_start_time_ms;
	pthread_mutex_t		print_lock;
	int					is_simulation_running;
	pthread_mutex_t		sim_state_lock;
}				t_simulation_config;

typedef enum e_philo_state
{
	STATE_THINKING,
	STATE_EATING,
	STATE_SLEEPING,
	STATE_DEAD,
}	t_philo_state;

typedef struct s_fork_pair
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_fork_pair;

typedef struct s_philo
{
	int					id;
	t_philo_state		state;
	int					meal_count;
	long				last_meal_time_ms;
	t_fork_pair			fork_pair;
	t_simulation_config	*config;
	pthread_mutex_t		meal_lock;
}					t_philo;

typedef struct s_death_monitor
{
	pthread_t			monitor_thread;
	int					all_philos_fed;
	t_simulation_config	*config;
}				t_death_monitor;

typedef struct s_simulation
{
	t_simulation_config	config;
	t_philo				*philos;
	pthread_t			*philo_threads;
	pthread_mutex_t		*fork_locks;
	t_death_monitor		death_monitor;
}					t_simulation;

#endif
