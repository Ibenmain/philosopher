/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 09:54:41 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/21 13:26:12 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_info
{
	int	nb_philo;
	int	t_eat;
	int	t_sleep;
	int	t_die;
	int	nb_eat;
}	t_info;

typedef struct s_philo
{
	t_info			*info;
	size_t			id;
	size_t			last_meal;
	long			nb_meals;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*sync;
	struct timeval	ts;
	int				pid;
	char			*lunch_name;
	sem_t			*lunch;
	int				finish;
}	t_philo;

int				ft_atoi(char *str);
char			*ft_itoa(int n);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_check_error(char **av);
int				ft_eat(t_philo *philo);
void			ft_param(int ac, char **av, t_info *info);
void			ft_print_msg(char *str);
sem_t			*ft_sem_init(char *name, unsigned int val);
int				launch_children(t_philo *philo, t_info *info, sem_t *forks, sem_t *print);
void			ft_set_philo(t_philo *philos, t_info *info, sem_t *forks, sem_t *print);
unsigned long	ft_get_ts(struct timeval ts);
size_t			ft_get_time(void);
void			ft_sleep(size_t ms);
void			*routine(void *arg);
int				ft_eat(t_philo *philo);
int				ft_fall_asleep(t_philo *philo);
int				ft_take_forks(t_philo *philo);
void			ft_print_msg(char *str);
void			ft_print(t_philo *philo, char *str);
int				is_dead(t_philo *philo);
void			ft_unlock_sync(sem_t *sync, unsigned int nb_philos);
int				watch_children(t_philo *philos, unsigned int nb_philos);
#endif