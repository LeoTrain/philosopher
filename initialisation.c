// HEADER

#include "philosopher.h"

int are_arguments_correct(int argc, char **argv, t_args *data_args)
{
	if (argc != 5 && argc != 6)
		return (0);
	data_args->number_of_philosophers = ft_atoi(argv[1]);
	if (data_args->number_of_philosophers <= 0)
		return (0);
	data_args->time_to_die = ft_atoi(argv[2]);
	data_args->time_to_eat = ft_atoi(argv[3]);
	data_args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data_args->number_to_eat = ft_atoi(argv[5]);
	else
		data_args->number_to_eat = 0;
	return (1);
}

int create_forks(t_args data_args, pthread_mutex_t **forks)
{
	int i;

	if (!data_args.number_of_philosophers)
		return (0);
	*forks = malloc(sizeof(pthread_mutex_t) * data_args.number_of_philosophers);
	if (!*forks)
		return (0);
	i = 0;
	while (i < data_args.number_of_philosophers)
	{
		if (pthread_mutex_init(&(*forks)[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int create_philosophers(t_args data_args, t_philosopher **philosophers, pthread_mutex_t *forks)
{
	int i;

	*philosophers = malloc(sizeof(t_philosopher) * data_args.number_of_philosophers);
	if (!*philosophers)
		return (0);
	i = 0;
	while (i < data_args.number_of_philosophers)
	{
		(*philosophers)[i].id = i + 1;
		(*philosophers)[i].meals_eaten = 0;
		(*philosophers)[i].last_meal_time = 0;
		(*philosophers)[i].args = data_args;
		(*philosophers)[i].left_fork = &forks[i];
		(*philosophers)[i].right_fork =
			&forks[(i + 1) % data_args.number_of_philosophers];
		pthread_mutex_init(&(*philosophers)[i].meal_mutex, NULL);
		i++;
	}
	return (1);
}

static void	check_is_dead(t_philosopher *data, int i)
{
   // printf("Is not eating: %d\n", !data[i].is_eating);
   // printf("Last meal time: %ld\n", (long)data[i].last_meal_time);
   // printf("diff between meal = %ld\n", get_time_in_ms() - (long)data[i].last_meal_time);
   // printf("Current time: %ld\n", get_current_time_in_ms(data[i].start_time));
   // printf("Time to die: %d\n", data[i].args.time_to_die);
   if (get_current_time_in_ms(data[i].start_time) == 0)
     return ;
	if (!data[i].is_eating &&
		(get_time_in_ms() - (long)data[i].last_meal_time) > data[i].args.time_to_die)
	{
		printf("Philosopher %d died.\n", data[i].id);
		exit(1);
	}
}

static void *death_check(void *philo_data)
{
	t_philosopher *data;
	int i;

	data = (t_philosopher *)philo_data;
	while (1)
	{
		i = 0;
		while (i < data->args.number_of_philosophers - 1)
		{
		    check_is_dead(data, i);
			i++;
		}
		usleep(1000 * data->args.time_to_die);
	}
	return (NULL);
}

int create_threads(pthread_t *threads, t_args data_args, t_philosopher *data_philo, pthread_t *death_thread)
{
	int i;

	if (!threads)
	{
		printf("Error allocating for threads.\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < data_args.number_of_philosophers)
	{
		pthread_create(&threads[i], NULL, philo_routine, &data_philo[i]);
		i++;
	}
	pthread_create(death_thread, NULL, death_check, (void *)data_philo);
	return (1);
}
