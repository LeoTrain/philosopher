#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define SUCCESS 0
# define FAILURE 1
# define ERROR_ARGS 2
# define ERROR_MALLOC 3
# define ERROR_MUTEX 4
# define ERROR_THREAD 5

typedef struct s_program_args
{
	int		philosopher_amount;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		max_meals;
}			t_program_args;

typedef struct s_philo
{
	int				id;
	long			meal_time_last;
	int				meal_amount_eaten;
	int				*completion_counter;
	t_program_args	*shared_data;
	pthread_mutex_t	*fork_left_mutex;
	pthread_mutex_t	*fork_right_mutex;
	pthread_mutex_t	*logging_mutex;
	pthread_mutex_t	*completion_counter_mutex;
}					t_philo;

typedef struct s_program
{
	t_program_args	args;
	t_philo			*philosophers;
	long			start_time;
	int				completion_counter;
	pthread_mutex_t	completion_counter_mutex;
	pthread_mutex_t	logging_mutex;
	pthread_mutex_t	*forks_mutex;

}					t_program;

int		ft_atoi(char *str);
long	ft_atol(char *str);
int		is_number(char *str);
long	get_current_time(void);
void	clean_forks(t_program *program, int i);
int		initialize_program_args(t_program_args *args);
int		parse_arguments(int argc, char **argv, t_program *program);
int		init_mutexes(t_program *program);
int		create_philosophers(t_program *program);
void	philo_think(long think_time_in_ms);
void	philo_sleep(long sleep_time_in_ms);
void	philo_eat(long eat_time_in_ms);
void	*philosophers_routine(void *philo_arg);

#endif
