/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifetime_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:17:07 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/22 16:17:11 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print(t_philo *philo, char *str)
{
	sem_wait(philo->print);
	printf("%lums %zu %s\n", get_ts(philo->ts), philo->id, str);
	sem_post(philo->print);
}

int	is_dead(t_philo *philo)
{
	if (*philo->stop == 1)
		return (1);
	sem_wait(philo->lunch);
	if (get_time() - philo->last_meal >= philo->info->t_die)
	{
		sem_post(philo->lunch);
		if (*philo->stop == 0)
		{
			*philo->stop = 1;
			sem_wait(philo->print);
			printf("%lums %zu died\n", get_ts(philo->ts), philo->id);
		}
		return (1);
	}
	sem_post(philo->lunch);
	return (0);
}

int	fall_asleep(t_philo *philo)
{
	if (*philo->stop == 1)
		return (0);
	ft_print(philo, "is sleeping");
	ft_sleep(philo->info->t_sleep);
	if (*philo->stop == 1)
		return (0);
	ft_print(philo, "is thinking");
	return (1);
}

int	eat(t_philo *philo)
{
	sem_wait(philo->lunch);
	philo->last_meal = get_time();
	ft_print(philo, "is eating");
	sem_post(philo->lunch);
	ft_sleep(philo->info->t_eat);
	philo->nb_meals += 1;
	sem_post(philo->forks);
	sem_post(philo->forks);
	if (*philo->stop == 1)
		return (0);
	return (1);
}

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		ft_sleep(2);
	while (*philo->stop == 0)
	{
		if (!take_forks(philo))
			break ;
		if (!eat(philo))
			break ;
		if (!fall_asleep(philo))
			break ;
	}
	return (NULL);
}
