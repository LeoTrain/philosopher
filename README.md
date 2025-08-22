Okay so this project is to understand threads.

First of we check the arguments passed.
- number of philosophers
- time to die (in milliseconds)
- time to eat (in milliseconds)
- time to sleep (in milliseconds)
- (optional) number of times each philosopher must eat
'''c
typedef struct s_args
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_to_eat;
} t_args;
'''

After that, we create the forks as a 'pthread_mutex_t'.
When the forks are created, we can also create the philosophers. They are their own structure:
'''c
typedef struct s_philosopher
{
	int id;
	int meals_eaten;
	int last_meal_time;
	int is_eating;
	int is_dead;
	int is_sleeping;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	struct s_args args;
} t_philosopher;
'''

When all this is done we can create/start the threads for each philosopher.
The 'routine' function is used for each thread with 'philosopher[i]'.
Then we also create/start another thread for the death check.

Finally we join all threads to finish the program.

### The routine:
- The routine is where each philosopher will think, eat, sleep.

### The death check:
- The death check is a function that constantly checks if a philo has eaten before his time went out so to say.
