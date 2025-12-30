#include <stdio.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>

typedef enum e_errors
{
	ERROR_NONE,
	ERROR_ARGC,
	ERROR_INVALID_ARG,
	ERROR_MEMORY,
	ERROR_THREAD,
	ERROR_MUTEX,
}				t_errors;

typedef struct s_data
{
	int		num_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_times_each_must_eat;
	long	start_time;
	pthread_mutex_t	print_mutex;
	int		simulation_running;
	pthread_mutex_t simulation_state_mutex;
}				t_data;

typedef enum e_philo_state
{
	STATE_THINKING,
	STATE_EATING,
	STATE_SLEEPING,
	STATE_DEAD,
}	t_philo_state;

typedef struct s_forks
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}					t_forks;

typedef struct s_philosopher
{
	int				id;
	t_philo_state	state;
	int				times_eaten;
	long			last_meal_time;
	t_forks			forks;
	t_data			*data;
	pthread_mutex_t	meal_time_mutex;
}					t_philosopher;

typedef struct s_monitor
{
	pthread_t	thread;
	int			all_ate_enough;
	t_data		*data;
}				t_monitor;

typedef struct s_simulation
{
	t_data			data;
	t_philosopher	*philosophers;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	t_monitor		monitor;
}					t_simulation;

t_errors ft_isdigit(char *str)
{
	int i;

	i = 0;
	if (!str || str[0] == '\0')
		return (ERROR_INVALID_ARG);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (ERROR_INVALID_ARG);
		i++;
	}
	return (ERROR_NONE);
}

t_errors ft_atoll(const char *str, long *out)
{
	long result;
	int i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (ERROR_INVALID_ARG);
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
			return (ERROR_INVALID_ARG);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	*out = result;
	return (ERROR_NONE);
}

long ft_getcurrenttime_in_ms(void)
{
	struct timeval	tv;
	long			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}

t_errors ft_isvalidargs(int argc, char **argv)
{
	int i;
	t_errors error;

	i = 1;
	while (i < argc)
	{
		error = ft_isdigit(argv[i]);
		if (error != ERROR_NONE)
			return (error);
		i++;
	}
	return (ERROR_NONE);
}

t_errors ft_initdata(int argc, char **argv, t_data *data)
{
	t_errors error;
	long value;

	error = ft_atoll(argv[1], &value);
	if (error != ERROR_NONE || value <= 0 || value > 200)
		return (ERROR_INVALID_ARG);
	data->num_philosophers = (int)value;
	error = ft_atoll(argv[2], &value);
	if (error != ERROR_NONE || value < 60)
		return (ERROR_INVALID_ARG);
	data->time_to_die = (int)value;
	error = ft_atoll(argv[3], &value);
	if (error != ERROR_NONE || value < 60)
		return (ERROR_INVALID_ARG);
	data->time_to_eat = (int)value;
	error = ft_atoll(argv[4], &value);
	if (error != ERROR_NONE || value < 60)
		return (ERROR_INVALID_ARG);
	data->time_to_sleep = (int)value;
	if (argc == 6)
	{
		error = ft_atoll(argv[5], &value);
		if (error != ERROR_NONE || value <= 0)
			return (ERROR_INVALID_ARG);
		data->num_times_each_must_eat = (int)value;
	}
	else
	{
		data->num_times_each_must_eat = -1;
	}
	data->simulation_running = 1;
	return (ERROR_NONE);
}

t_errors ft_initforks(t_simulation *simulation)
{
	int i;
	simulation->forks = malloc(sizeof(pthread_mutex_t) * simulation->data.num_philosophers);
	if (simulation->forks == NULL)
		return (ERROR_MEMORY);
	i = 0;
	while (i < simulation->data.num_philosophers)
	{
		if (pthread_mutex_init(&simulation->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&simulation->forks[i]);
			free(simulation->forks);
			return (ERROR_MUTEX);
		}
		i++;
	}
	if (pthread_mutex_init(&simulation->data.print_mutex, NULL) != 0)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&simulation->forks[i]);
		free(simulation->forks);
		return (ERROR_MUTEX);
	}
	if (pthread_mutex_init(&simulation->data.simulation_state_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&simulation->data.print_mutex);
		i = simulation->data.num_philosophers;
		while (--i >= 0)
			pthread_mutex_destroy(&simulation->forks[i]);
		free(simulation->forks);
		return (ERROR_MUTEX);
	}
	return (ERROR_NONE);
}

t_errors ft_initphilosophers(t_simulation *simulation)
{
	int i;
	simulation->philosophers = malloc(sizeof(t_philosopher) * simulation->data.num_philosophers);
	if (simulation->philosophers == NULL)
		return (ERROR_MEMORY);
	i = 0;
	while (i < simulation->data.num_philosophers)
	{
		simulation->philosophers[i].id = i + 1;
		simulation->philosophers[i].state = STATE_THINKING;
		simulation->philosophers[i].times_eaten = 0;
		simulation->philosophers[i].last_meal_time = 0;
		simulation->philosophers[i].data = &simulation->data;
		simulation->philosophers[i].forks.left = &simulation->forks[i];
		simulation->philosophers[i].forks.right = &simulation->forks[(i + 1) % simulation->data.num_philosophers];
		if (pthread_mutex_init(&simulation->philosophers[i].meal_time_mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&simulation->philosophers[i].meal_time_mutex);
			free(simulation->philosophers);
			return (ERROR_MUTEX);
		}
		i++;
	}
	return (ERROR_NONE);
}

int check_simulation_ended(t_data *data)
{
	int ended;
	pthread_mutex_lock(&data->simulation_state_mutex);
	ended = !data->simulation_running;
	pthread_mutex_unlock(&data->simulation_state_mutex);
	return (ended);
}

void stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->simulation_state_mutex);
	data->simulation_running = 0;
	pthread_mutex_unlock(&data->simulation_state_mutex);
}

t_errors log_action(t_philosopher *philo, const char *action)
{
	long current_time;

	if (check_simulation_ended(philo->data))
		return (ERROR_NONE);
	current_time = ft_getcurrenttime_in_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	if (philo->data->simulation_running)
		printf("%ld %d %s\n", current_time, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (ERROR_NONE);
}

t_errors lock_forks(t_philosopher *philo)
{
	if (philo->data->num_philosophers == 1)
	{
		pthread_mutex_lock(philo->forks.left);
		log_action(philo, "has taken a fork");
		pthread_mutex_unlock(philo->forks.left);
		return (ERROR_NONE);
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->forks.right);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->forks.left);
		log_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->forks.left);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->forks.right);
		log_action(philo, "has taken a fork");
	}
	return (ERROR_NONE);
}

t_errors unlock_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->forks.left);
	pthread_mutex_unlock(philo->forks.right);
	return (ERROR_NONE);
}

t_errors update_last_meal(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = ft_getcurrenttime_in_ms();
	pthread_mutex_unlock(&philo->meal_time_mutex);
	return (ERROR_NONE);
}

void ft_precise_usleep(long duration_ms)
{
	long start;
	long target;

	start = ft_getcurrenttime_in_ms();
	target = start + duration_ms;
	while (ft_getcurrenttime_in_ms() < target)
		usleep(500);
}

t_errors philo_eat(t_philosopher *philo)
{
	t_errors error;

	if (philo->data->num_philosophers == 1)
	{
		lock_forks(philo);
		ft_precise_usleep(philo->data->time_to_die + 1);
		return (ERROR_NONE);
	}
	error = lock_forks(philo);
	if (error != ERROR_NONE || check_simulation_ended(philo->data))
	{
		unlock_forks(philo);
		return (error);
	}
	error = update_last_meal(philo);
	if (error != ERROR_NONE)
	{
		unlock_forks(philo);
		return (error);
	}
	log_action(philo, "is eating");
	ft_precise_usleep(philo->data->time_to_eat);
	philo->times_eaten++;
	error = unlock_forks(philo);
	if (error != ERROR_NONE)
		return (error);
	return (ERROR_NONE);
}

t_errors philo_think(t_philosopher *philo)
{
	log_action(philo, "is thinking");
	if (philo->data->num_philosophers % 2 != 0)
	{
		long think_time = (philo->data->time_to_eat * 2 - philo->data->time_to_sleep) / 2;
		if (think_time > 0)
			ft_precise_usleep(think_time);
	}
	return (ERROR_NONE);
}

t_errors philo_sleep(t_philosopher *philo)
{
	log_action(philo, "is sleeping");
	ft_precise_usleep(philo->data->time_to_sleep);
	return (ERROR_NONE);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	philo = (t_philosopher *)arg;

	if (philo->id % 2 == 0)
		usleep(1000);

	while (1)
	{
		if (check_simulation_ended(philo->data))
			break ;
		if (philo->data->num_times_each_must_eat != -1 && philo->times_eaten >= philo->data->num_times_each_must_eat)
			break ;
		philo_think(philo);
		if (check_simulation_ended(philo->data))
			break ;
		philo_eat(philo);
		if (check_simulation_ended(philo->data))
			break ;
		philo_sleep(philo);
	}
	return (NULL);
}

t_errors ft_initstarttime(t_simulation *simulation)
{
	int i;

	i = 0;
	simulation->data.start_time = ft_getcurrenttime_in_ms();
	if (simulation->data.start_time == 0)
		return (ERROR_MEMORY);
	while (i < simulation->data.num_philosophers)
	{
		simulation->philosophers[i].last_meal_time = simulation->data.start_time;
		i++;
	}
	return (ERROR_NONE);
}

t_errors ft_initthreads(t_simulation *simulation)
{
	int i;
	t_errors error;

	simulation->threads = malloc(sizeof(pthread_t) * simulation->data.num_philosophers);
	if (simulation->threads == NULL)
		return (ERROR_MEMORY);
	i = 0;
	error = ft_initstarttime(simulation);
	if (error != ERROR_NONE)
	{
		free(simulation->threads);
		return (error);
	}
	while (i < simulation->data.num_philosophers)
	{
		if (pthread_create(&simulation->threads[i], NULL, philosopher_routine, (void *)&simulation->philosophers[i]) != 0)
		{
			stop_simulation(&simulation->data);
			while (--i >= 0)
				pthread_join(simulation->threads[i], NULL);
			free(simulation->threads);
			return (ERROR_THREAD);
		}
		i++;
	}
	return (ERROR_NONE);
}

t_errors ft_jointhreads(t_simulation *simulation)
{
	int i;
	i = 0;

	while (i < simulation->data.num_philosophers)
	{
		if (pthread_join(simulation->threads[i], NULL))
			return (ERROR_THREAD);
		i++;
	}
	if (pthread_join(simulation->monitor.thread, NULL) != 0)
		return (ERROR_THREAD);
	return (ERROR_NONE);
}

int check_all_ate_enough(t_simulation *simulation)
{
	int i;
	int all_done;

	if (simulation->data.num_times_each_must_eat == -1)
		return (0);
	all_done = 1;
	i = 0;
	while (i < simulation->data.num_philosophers)
	{
		pthread_mutex_lock(&simulation->philosophers[i].meal_time_mutex);
		if (simulation->philosophers[i].times_eaten < simulation->data.num_times_each_must_eat)
			all_done = 0;
		pthread_mutex_unlock(&simulation->philosophers[i].meal_time_mutex);
		if (!all_done)
			break;
		i++;
	}
	return (all_done);
}

void *monitor_routine(void *arg)
{
	t_simulation	*simulation;
	int				i;
	long			current_time;

	simulation = (t_simulation *)arg;
	usleep(1000);
	while (1)
	{
		i = 0;
		while (i < simulation->data.num_philosophers)
		{
			pthread_mutex_lock(&simulation->philosophers[i].meal_time_mutex);
			current_time = ft_getcurrenttime_in_ms();
			if (current_time - simulation->philosophers[i].last_meal_time > simulation->data.time_to_die)
			{
				pthread_mutex_lock(&simulation->data.simulation_state_mutex);
				simulation->data.simulation_running = 0;
				pthread_mutex_unlock(&simulation->data.simulation_state_mutex);
				pthread_mutex_lock(&simulation->data.print_mutex);
				printf("%ld %d died\n", current_time - simulation->data.start_time, simulation->philosophers[i].id);
				pthread_mutex_unlock(&simulation->data.print_mutex);
				pthread_mutex_unlock(&simulation->philosophers[i].meal_time_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&simulation->philosophers[i].meal_time_mutex);
			i++;
		}
		if (check_all_ate_enough(simulation))
		{
			stop_simulation(&simulation->data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

t_errors ft_initmonitor(t_simulation *simulation)
{
	if (pthread_create(&simulation->monitor.thread, NULL, monitor_routine, (void *)simulation) != 0)
		return (ERROR_THREAD);
	return (ERROR_NONE);
}

void cleanup_simulation(t_simulation *simulation, int init_level)
{
	int i;

	if (init_level >= 5)
		ft_jointhreads(simulation);
	if (init_level >= 4 && simulation->threads)
		free(simulation->threads);
	if (init_level >= 3 && simulation->philosophers)
	{
		i = 0;
		while (i < simulation->data.num_philosophers)
		{
			pthread_mutex_destroy(&simulation->philosophers[i].meal_time_mutex);
			i++;
		}
		free(simulation->philosophers);
	}
	if (init_level >= 2 && simulation->forks)
	{
		pthread_mutex_destroy(&simulation->data.simulation_state_mutex);
		pthread_mutex_destroy(&simulation->data.print_mutex);
		i = 0;
		while (i < simulation->data.num_philosophers)
		{
			pthread_mutex_destroy(&simulation->forks[i]);
			i++;
		}
		free(simulation->forks);
	}
}

int main(int argc, char **argv)
{
	t_simulation	simulation;
	t_errors		error;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (ERROR_ARGC);
	}
	error = ft_isvalidargs(argc, argv);
	if (error != ERROR_NONE)
	{
		printf("Invalid argument detected\n");
		return (error);
	}
	error = ft_initdata(argc, argv, &simulation.data);
	if (error != ERROR_NONE)
	{
		printf("Error initializing data\n");
		return (error);
	}
	error = ft_initforks(&simulation);
	if (error != ERROR_NONE)
	{
		printf("Error initializing forks\n");
		return (error);
	}
	error = ft_initphilosophers(&simulation);
	if (error != ERROR_NONE)
	{
		printf("Error initializing philosophers\n");
		cleanup_simulation(&simulation, 2);
		return (error);
	}
	error = ft_initthreads(&simulation);
	if (error != ERROR_NONE)
	{
		printf("Error initializing threads\n");
		cleanup_simulation(&simulation, 3);
		return (error);
	}
	error = ft_initmonitor(&simulation);
	if (error != ERROR_NONE)
	{
		printf("Error initializing monitor\n");
		stop_simulation(&simulation.data);
		cleanup_simulation(&simulation, 4);
		return (error);
	}
	error = ft_jointhreads(&simulation);
	if (error != ERROR_NONE)
	{
		printf("Error joining threads\n");
		cleanup_simulation(&simulation, 4);
		return (error);
	}
	cleanup_simulation(&simulation, 4);
	return (EXIT_SUCCESS);
}
