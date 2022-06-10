NAME = philo
INC  = philo.h
SRCS = 	main.c \
		parsing.c\
		utile.c\
		forks.c\
		philo.c\
		routine.c\
		time.c\
		death.c

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -rf

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $^

%.o: %.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all