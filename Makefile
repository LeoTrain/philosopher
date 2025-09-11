NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
S_CORE = srcs/core/main.c srcs/core/cleanup.c
S_INIT = srcs/init/parse_args.c srcs/init/init_args.c srcs/init/init_mutexes.c srcs/init/init_philosophers.c
S_LOGIC = srcs/logic/philosophers_routine.c srcs/logic/eat.c srcs/logic/sleep_think.c srcs/logic/death_check.c
S_UTILS = srcs/utils/time_utils.c srcs/utils/string_utils.c srcs/utils/logging.c srcs/utils/philo_utils.c
SRCS = $(S_CORE) $(S_INIT) $(S_LOGIC) $(S_UTILS)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all


