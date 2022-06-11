/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:41:00 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/11 18:06:28 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*ft_creat_fork(t_info *info)
{
	int				i;
	pthread_mutex_t	*fork;

	i = 0;
	fork = malloc(sizeof(pthread_mutex_t) * info->nb_philo);
	if (!fork)
		return (0);
	while (i < info->nb_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (fork);
}

void	ft_get_forks(t_philo *philo, size_t index, pthread_mutex_t *forks,
				unsigned int nb_philo)
{
	if (index == 0)
	{
		philo->l_fork = &forks[nb_philo - 1];
		philo->r_fork = &forks[0];
	}
	else
	{
		philo->l_fork = &forks[index - 1];
		philo->r_fork = &forks[index];
	}
}
