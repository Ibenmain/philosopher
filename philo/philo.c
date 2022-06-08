/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 01:18:16 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/08 03:36:58 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_philo(t_philo *philos, t_info *info, pthread_mutex_t *print)
{
	int				i;
	int				finish;
	struct timeval	time;

	i = 0;
	finish = 0;
	gettimeofday(&time, NULL);
	while (i < info->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].nb_meals = 0;
		philos[i].info = info;
		philos[i].print = print;
		philos[i].finish = &finish;
		philos[i].ts = time;
		philos[i].last_meal = ft_get_time();
		i++;
	}
}

int	ft_start_lunch(t_info *info, pthread_mutex_t *fork,
			pthread_mutex_t *print)
{
	int				i;
	t_philo			*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * info->nb_philo);
	if (!philo)
		return (0);
	ft_set_philo(philo, info, print);
	while (i < info->nb_philo)
	{
		pthread_mutex_init(&philo[i].lunch, NULL);
		ft_get_forks(&philo[i], i, fork, info->nb_philo);
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (0);
		i++;
	}
	return (1);
}
