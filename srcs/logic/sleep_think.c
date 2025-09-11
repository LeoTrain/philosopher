#include "../../includes/philo.h"

void	philo_sleep(long sleep_time_in_ms)
{
	usleep(sleep_time_in_ms);
}

void	philo_think(long think_time_in_ms)
{
	usleep(think_time_in_ms);
}
