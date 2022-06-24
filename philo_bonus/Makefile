NAME = philo_bonus
INC = philo_bonus.h
COMP_LINUX = -lpthread
SRCS_B = main_bonus.c \
		check.c \
		ft_itoa.c \
		ft_strjoin.c \
		utils.c \
		philo_bonus.c \
		lifetime_bonus.c \
		forks_bonus.c

OBJS_B = $(SRCS_B:%.c=%.o)
CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -f

all:$(NAME)

$(NAME): $(OBJS_B)
	@$(CC) $(CFLAGS) -o $(NAME) $^ $(COMP_LINUX)


%.o: %.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(RM) $(OBJS_B)

fclean : clean
	@$(RM) $(NAME)

re : fclean all