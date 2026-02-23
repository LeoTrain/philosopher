*This project has been created as part of 42 curriculum by leberton"

# Philosophers

## Description
Simulating the classic Dining Philosophers problem using threads and mutexes in C.

One or more philos sit around a table. Each of them alternates between eating, thinking and sleeping. There is one fork between each pair of philo. And they all need 2 forks to eat. If a philosopher has not started eating within `time_to_die` milliseconds since their last meal ( or the start of the sim ), they die and the simulation stops.

The goal is to keep every philo alive by preventing deadlocks and starvation


## Instruction
### Compilation
```bash
make
```

### Usage
```bash
./philo nb_philo time_to_die time_to_eat time_to_sleep [max_meals]
```
|Arguments|Description|
|---------|-----------|
|`nb_philo`|Number of philosophers ( and forks ) on the table|
|`time_to_die`|Time in ms before a philo dies without eating|
|`time_to_eat`|Time in ms a philo spends eating|
|`time_to_sleep`|Time in ms a philo spends sleeping|
|`[max_meals]`|(optional) Simulation stops when all philos ate this many times|

### Examples
```bash
./philo 5 800 200 200 # no one should die
./philo 5 800 200 200 7 # stops after reaching 7 meals each
./philo 4 310 200 100 # One will die
```

### Cleanup
```bash
make clean  # removes object files
make fclean # removes object files and executable
make re     # full recompilation
```


## Resources
- https://medium.com/@akshatarhabib/understanding-threads-in-c-c9feb5e9372a
- https://www.youtube.com/watch?v=ldJ8WGZVXZk
- https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/
- https://man7.org/linux/man-pages/man7/pthreads.7.html
- https://www.youtube.com/watch?v=IKG1P4rgm54&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=2
- https://www.youtube.com/watch?v=IKG1P4rgm54&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=3
- https://www.youtube.com/watch?v=IKG1P4rgm54&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=4
- https://www.youtube.com/watch?v=IKG1P4rgm54&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=5
- etc..

### AI Usage
AI (claude) was used to do the following things:
- Explaining concepts
- Reviewing and explaining data race risks
- Helping structure the project into logical directories

All code was written, understood and tested by me, myself and I !!!
