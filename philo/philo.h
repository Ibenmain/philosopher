/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:58:26 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/11 15:57:34 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

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
	int				*finish;
	pthread_mutex_t	*print;
	pthread_mutex_t	lunch;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		thread;
	struct timeval	ts;

}	t_philo;

int				ft_atoi(char *str);
int				ft_check_error(char **av);
int				ft_eat(t_philo *philo);
int				ft_fall_asleep(t_philo *philo);
void			ft_param(int ac, char **av, t_info *info);
void			ft_print(t_philo *philo, char *str);
void			ft_print_msg(char *str);
pthread_mutex_t	*ft_creat_fork(t_info *info);
size_t			ft_get_time(void);
void			ft_sleep(size_t ms);
unsigned long	ft_get_ts(struct timeval ts);
void			*routine(void *arg);
void			join_philo(t_philo *philo);
int				ft_check_die_of_philo(t_philo *philo);
int				ft_check_meals(t_philo *phli, t_info *info);
int				ft_is_dead(t_philo *philo);
int				ft_check_death(t_info *info, t_philo *philo, pthread_mutex_t *fork);
void			ft_get_forks(t_philo *philo, size_t index, pthread_mutex_t *forks, unsigned int nb_philo);
void			ft_set_philo(t_philo *philos, t_info *info, pthread_mutex_t *print);
int				ft_start_lunch(t_philo *philo, t_info *info, pthread_mutex_t *fork, pthread_mutex_t *print);
int				take_forks(t_philo *philo, pthread_mutex_t *forkl, pthread_mutex_t *forkr);
int				watch_threads(t_info *utils, t_philo *philos, unsigned int nb_philos, pthread_mutex_t *forks);
void			destroy_forks(pthread_mutex_t *forks, t_info *utils);
#endif