/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:59:59 by aanjaimi          #+#    #+#             */
/*   Updated: 2022/06/21 22:52:34 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_children(t_philo *philos, unsigned int nb_philos)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
	{
		kill(philos[i].pid, SIGKILL);
		i++;
	}
	i = 0;
	while (i < nb_philos)
	{
		sem_close(philos[i].lunch);
		sem_unlink(philos[i].lunch_name);
		free(philos[i].lunch_name);
		i++;
	}
}

int	watch_children(t_philo *philos, unsigned int nb_philos)
{
	size_t	nb_full;
	int		status;

	nb_full = 0;
	while (philos->utils->nb_eat > 0 && nb_full != nb_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != ATE_ENOUGH)
			break ;
		nb_full++;
	}
	if (philos->utils->nb_eat < 0)
		waitpid(-1, &status, 0);
	kill_children(philos, nb_philos);
	if (philos->utils->nb_eat && nb_full == nb_philos)
		printf("Everyone ate well\n");
	sem_close(philos->forks);
	sem_unlink("forks");
	sem_close(philos->sync);
	sem_unlink("sync");
	sem_post(philos->print);
	free(philos);
	return (1);
}

void	process(t_philo *philo)
{
	pthread_t	thread;
	bool		stop;

	stop = false;
	philo->stop = &stop;
	sem_wait(philo->sync);
	philo->last_meal = get_time();
	if (pthread_create(&thread, NULL, &live, philo)
		|| pthread_detach(thread))
		exit(ERR);
	while (1)
	{
		ft_sleep(4);
		if (is_dead(philo))
			exit(IS_DEAD);
		else if (philo->utils->nb_eat > 0
			&& philo->nb_meals >= philo->utils->nb_eat)
			exit(ATE_ENOUGH);
	}	
}

int	set_philos(t_philo *philos, t_info *utils, sem_t *print)
{
	size_t	i;
	sem_t	*forks;

	i = 0;
	forks = init_forks(utils);
	if (!forks)
		return (0);
	while (i < utils->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].nb_meals = 0;
		philos[i].utils = utils;
		philos[i].print = print;
		philos[i].forks = forks;
		philos[i].lunch_name = ft_strjoin("lunch_", ft_itoa(i));
		philos[i].lunch = ft_sem_init(philos[i].lunch_name, 1);
		i++;
	}
	return (1);
}

int	launch_children(t_info *utils, sem_t *print)
{
	t_philo			*philos;
	size_t			i;
	sem_t			*sync;
	struct timeval	time;

	i = 0;
	sync = ft_sem_init("sync", 0);
	philos = malloc(sizeof(t_philo) * utils->nb_philo);
	if (!philos || !set_philos(philos, utils, print))
		return (0);
	gettimeofday(&time, NULL);
	while (i < utils->nb_philo)
	{
		philos[i].sync = sync;
		philos[i].pid = fork();
		philos[i].ts = time;
		if (!philos[i].pid)
			process(&philos[i]);
		else if (philos[i].pid < 0)
			return (0);
		i++;
	}
	unlock_sync(sync, utils->nb_philo);
	return (watch_children(philos, utils->nb_philo));
}
