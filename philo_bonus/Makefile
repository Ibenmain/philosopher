NAME = philo_bonus
INC  = philo_bonus.h
SRCS = 	main_bonus.c \
		philo_bonus.c\
		parsing_bonus.c\
		utile_bonus.c\
		time_bonus.c\
		routine_bonus.c\
		death_bonus.c\
		watch_children.c

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