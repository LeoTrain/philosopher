#include "../../includes/philo.h"

void	clean_forks(t_program *program, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&program->forks_mutex[i]);
		i--;
	}
	free(program->forks_mutex);
	program->forks_mutex = NULL;
}
