NAME = 		philo
CC = 		cc
CFLAGS = 	-Wall -Wextra -Werror -pthread

S_CORE = 	srcs/core/program_main.c
S_INIT = 	srcs/init/program_init.c \
		 	srcs/init/mutex_init.c \
		 	srcs/init/philo_setup.c
S_PARSE = 	srcs/parse/arg_parsing.c \
		  	srcs/parse/arg_validation.c
S_ROUTINE = srcs/routine/main_routine.c \
			srcs/routine/single_philo.c \
			srcs/routine/fork_management.c \
			srcs/routine/fork_unlock.c \
			srcs/routine/meal_check.c
S_THREAD = 	srcs/thread/thread_create.c \
		   	srcs/thread/thread_cleanup.c \
		   	srcs/thread/death_monitor.c
S_ACTIONS = srcs/actions/philo_actions.c
S_OUTPUT = 	srcs/output/log_actions.c \
		   	srcs/output/log_status.c
S_UTILS =	srcs/utils/time_helpers.c \
		  	srcs/utils/death_check.c \
		  	srcs/utils/string_helpers.c \
		  	srcs/utils/string_convert.c \
		  	srcs/utils/string_long.c

RED =		"\033[31m"
BLUE =		"\033[34m"
YELLOW =	"\033[33m"
RESET = 	"\033[0m"

SRCS = $(S_CORE) $(S_INIT) $(S_PARSE) $(S_ROUTINE) $(S_THREAD) $(S_ACTIONS) $(S_OUTPUT) $(S_UTILS)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(BLUE)"Compiling objects into executable"$(RESET)
	@$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	@echo $(YELLOW)"Compiling $^ into a object file"$(RESET)
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@echo $(RED)"Cleaning object files"$(RESET)
	@rm -f $(OBJS)

fclean: clean
	@echo $(RED)"Cleaning executable"$(RESET)
	@rm -f $(NAME)

re: fclean all


