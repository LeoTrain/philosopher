NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = srcs/main.c \
	   srcs/cleanup.c \
	   srcs/monitor_death.c \
	   srcs/philo_lifecycle.c \
	   srcs/thread_management.c \
	   srcs/actions/forks.c \
	   srcs/actions/philo.c \
	   srcs/init/config.c \
	   srcs/init/mutex.c \
	   srcs/init/philo.c \
	   srcs/utils/simulation.c \
	   srcs/utils/time.c \
	   srcs/utils/validation.c \

OBJS = $(SRCS:.c=.o)

BLUE = \033[0;34m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: (NAME)

(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiled $<$(RESET)"

clean:
	@rm -f $(OBJS)
	@echo "$(YELLOW)Object files removed!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) executable removed!$(RESET)"

re: fclean all
