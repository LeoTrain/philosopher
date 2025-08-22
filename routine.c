// HEADER

#include "philosopher.h"

static void	log_philo(char *str, long start_time, int id)
{
		printf("%ld %d %s\n", get_current_time_in_ms(start_time), id, str);
}

static void eat(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		log_philo("has taken right fork.", philo->start_time, philo->id);
		pthread_mutex_lock(philo->left_fork);
		log_philo("has taken left fork.", philo->start_time, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		log_philo("has taken left fork.",philo->start_time, philo->id);
		pthread_mutex_lock(philo->right_fork);
		log_philo("has taken right fork.", philo->start_time, philo->id);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->is_eating = 1;
	philo->last_meal_time = get_time_in_ms();
	log_philo("is eating.", philo->start_time, philo->id);
	usleep(philo->args.time_to_eat * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		log_philo("has put down left fork.", philo->start_time, philo->id);
		pthread_mutex_unlock(philo->right_fork);
		log_philo("has put down right fork.", philo->start_time, philo->id);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		log_philo("has put down right fork.", philo->start_time, philo->id);
		pthread_mutex_unlock(philo->left_fork);
		log_philo("has put down left fork.", philo->start_time, philo->id);
	}
	philo->is_eating = 0;
}

static void philo_sleep(t_philosopher *philo)
{
	log_philo("is sleeping.", philo->start_time, philo->id);
	philo->is_sleeping = 1;
	usleep(philo->args.time_to_sleep * 1000);
	philo->is_sleeping = 0;
}

static void think(t_philosopher *philo)
{
	log_philo("is thinking.", philo->start_time, philo->id);
	usleep(2000);
}

void *philo_routine(void *philosopher)
{
	t_philosopher *philo;

	philo = (t_philosopher *)philosopher;
	while (philo->args.number_to_eat == 0 ||
		   philo->meals_eaten < philo->args.number_to_eat)
	{
		eat(philo);
		think(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
