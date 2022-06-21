/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:06:32 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/21 15:28:20 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*ft_sem_init(char *name, unsigned int val)
{
	sem_t	*semaphor;

	sem_unlink(name);
	semaphor = sem_open(name, O_CREAT, 0777, val);
	if (semaphor != SEM_FAILED)
		return (semaphor);
	sem_unlink(name);
	return (sem_open(name, O_CREAT, 0777, val));
}

void	ft_set_philo(t_philo *philos, t_info *info, sem_t *forks, sem_t *print)
{
	int				i;

	i = 0;
	while (i < info->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].nb_meals = 0;
		philos[i].info = info;
		philos[i].print = print;
		philos[i].fork = forks;
		philos[i].lunch_name = ft_strjoin("lunch_", ft_itoa(i));
		philos[i].lunch = ft_sem_init(philos[i].lunch_name, 1);
		i++;
	}
}

void	process(t_philo *philo)
{
	pthread_t	thread;
	int			fin;

	fin = 0;
	philo->finish = fin;
	sem_wait(philo->sync);
	philo->last_meal = ft_get_time();
	if (pthread_create(&thread, NULL, &routine, philo) == -1
		|| pthread_detach(thread))
		exit(1);
	// while (1)
	// {
	// 	ft_sleep(4);
	// 	if (is_dead(philo))
	// 		exit(0);
	// 	else if (philo->info->nb_eat > 0
	// 		&& philo->nb_meals >= philo->info->nb_eat)
	// 		exit(1);
	// }
	while (1);
}

int	launch_children(t_philo *philo, t_info *info, sem_t *forks, sem_t *print)
{
	struct timeval	time;
	int				i;
	sem_t			*sync;

	i = 0;
	sync = ft_sem_init("sync", 0);
	ft_set_philo(philo, info, forks, print);
	gettimeofday(&time, NULL);
	while (i < info->nb_philo)
	{
		philo[i].pid = fork();
		philo[i].ts = time;
		philo[i].sync = sync;
		if (!philo[i].pid)
			process(&philo[i]);
		else if (philo[i].pid < 0)
			return (0);
		i++;
	}
	ft_unlock_sync(sync, info->nb_philo);
	//watch_children(philo, info->nb_philo);
	// while (i < info->nb_philo)
	// {
		
	// }
	return (1);
}
