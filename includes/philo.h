#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

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
	long	start_time;
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
	pthread_mutex_t	*someone_died_mutex;
}					t_philo;


typedef struct s_program
{
	t_program_args			args;
	t_philo					*philosophers;
	int						completion_counter;
	int						someone_died;
	pthread_t				*threads;
	pthread_mutex_t			completion_counter_mutex;
	pthread_mutex_t			logging_mutex;
	pthread_mutex_t			*forks_mutex;
	pthread_mutex_t			someone_died_mutex;
	struct s_thread_data	*thread_data;
}							t_program;

typedef struct s_thread_data
{
	t_philo		*philo;
	t_program	*program;
}				t_thread_data;


int		ft_atoi(char *str);
long	ft_atol(char *str);
int		is_number(char *str);
long	get_current_time(void);
long	get_elapsed_time(long start_time);
int		is_dead(t_thread_data *thread_data);
int		someone_died(t_thread_data *thread_data);
void	log_fork(t_philo *philo);
void	log_meal(t_philo *philo);
void	log_sleep(t_philo *philo);
void	log_think(t_philo *philo);
void	log_dead(t_philo *philo);
void	clean_forks(t_program *program, int i);
int		initialize_program_args(t_program_args *args);
int		parse_arguments(int argc, char **argv, t_program *program);
int		check_args(t_program_args args);
int		init_mutexes(t_program *program);
void	add_start_time_to_args(t_program *program);
int		create_philosophers(t_program *program);
int		create_and_start_threads(t_program *program);
void	join_threads(t_program *program);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);
void	*philosophers_routine(void *arg);
void	*handle_single_philosopher(t_thread_data *thread_data);
void	lock_mutexes(t_philo *philo);
void	unlock_mutexes(t_philo *philo);
int		check_meal_completion(t_thread_data *thread_data);

#endif
