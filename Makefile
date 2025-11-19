NAME		=	philo
CC			=	cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM			=	rm -f

SRCS		=	src/main.c \
				src/initialize_data.c \
				src/create_threads.c \
				src/routine.c \
				src/utils.c \
				src/cleanup.c \
				src/monitor_death.c

OBJS		=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
