#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_args
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_to_eat;
} t_args;

typedef struct s_philosopher
{
	int id;
	int meals_eaten;
	int last_meal_time;
	int is_eating;
	int is_dead;
	int is_sleeping;
	long start_time;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	struct s_args args;
} t_philosopher;

typedef struct s_philo_data
{
	t_args args;
	t_philosopher *philos;
	pthread_mutex_t *forks;
	pthread_t *threads;
	pthread_t death_thread;
	long start_time;
	int stopped;
} t_philo_data;

int ft_atoi(const char *str);
long get_time_in_ms(void);
long	get_current_time_in_ms(long start_time);
int are_arguments_correct(int argc, char **argv, t_args *data_args);
int create_philosophers(t_args data_args, t_philosopher **philosophers,
						pthread_mutex_t *forks);
int create_forks(t_args data_args, pthread_mutex_t **forks);
int create_threads(pthread_t *threads, t_args data_args,
				   t_philosopher *data_philo, pthread_t *death_thread);
void *philo_routine(void *philosopher);

#endif
