// HEADER

#include "philosopher.h"

static void	init_threads(t_philo_data *data)
{
    int	i;

	data->start_time = get_time_in_ms();
	i = 0;
	while (i < data->args.number_of_philosophers)
	{
			data->philos[i].start_time = data->start_time;
			i++;
	}
	if (!create_threads(data->threads, data->args, data->philos,
						&data->death_thread))
	{
		printf("Error creating threads.\n");
		exit(EXIT_FAILURE);
	}
}

static void	init_data(t_philo_data *data, int argc, char **argv)
{
	if (!are_arguments_correct(argc, argv, &data->args))
	{
		printf(
			"Wrong arguments, correct use: ./philo <number_of_philo> "
			"<time_to_die> <time_to_eat> <time_to_sleep> /<amount_to_eat>\n");
		exit(EXIT_FAILURE);
	}
	if (!create_forks(data->args, &data->forks))
	{
		printf("Error creating forks.\n");
		exit(EXIT_FAILURE);
	}
	if (!create_philosophers(data->args, &data->philos, data->forks))
	{
		printf("Error creating philosphers.\n");
		exit(EXIT_FAILURE);
	}
	init_threads(data);
}

static void	join_threads(t_philo_data *data)
{
    int	i;

	i = 0;
	while (i < data->args.number_of_philosophers)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
	pthread_join(data->death_thread, NULL);
}

int main(int argc, char **argv)
{
	t_philo_data	data;

	init_data(&data, argc, argv);
	join_threads(&data);
	return (0);
}
