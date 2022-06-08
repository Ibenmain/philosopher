/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 03:21:50 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/08 03:55:29 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->print);
	printf("%lums %zu %s\n", ft_get_ts(philo->ts), philo->id, str);
	pthread_mutex_unlock(philo->print);
}

int	ft_take_forks(t_philo *philo, pthread_mutex_t *forkl,
			pthread_mutex_t *forkr)
{
	if (*philo->finish == 1)
		return (0);
	pthread_mutex_lock(forkl);
	if (*philo->finish == 1)
		return (0);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(forkr);
	if (*philo->finish == 1)
		return (0);
	ft_print(philo, "has taken a fork");
	return (1);
}

int	ft_fall_asleep(t_philo *philo)
{
	if (*philo->finish == 1)
		return (0);
	ft_print(philo, "is sleeping");
	ft_sleep(philo->info->t_sleep);
	if (*philo->finish == 1)
		return (0);
	ft_print(philo, "is thinking");
	return (1);
}

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lunch);
	philo->last_meal = ft_get_time();
	ft_print(philo, "is eating");
	pthread_mutex_unlock(&philo->lunch);
	ft_sleep(philo->info->t_eat);
	philo->nb_meals += 1;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (*philo->finish == 1)
		return (0);
	return (1);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;

	if (philo->id % 2)
		ft_sleep(2);
	while (*philo->finish == 0)
	{
		if (!ft_take_forks(philo, philo->l_fork, philo->r_fork))
			break ;
		if (!ft_eat(philo))
			break ;
		if (!ft_fall_asleep(philo))
			break ;
	}
	return (NULL);
}
