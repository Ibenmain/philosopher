/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:35:02 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/20 13:57:18 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print(t_philo *philo, char *str)
{
	sem_wait(philo->print);
	printf("%lums %zu %s\n", ft_get_ts(philo->ts), philo->id, str);
	sem_post(philo->print);
}

int	ft_take_forks(t_philo *philo)
{
	if (philo->finish == 1)
		return (0);
	sem_wait(philo->fork);
	if (philo->finish == 1)
		return (0);
	ft_print(philo, "has taken a fork");
	sem_wait(philo->fork);
	if (philo->finish == 1)
		return (0);
	ft_print(philo, "has taken a fork");
	return (1);
}

int	ft_fall_asleep(t_philo *philo)
{
	if (philo->finish == 1)
		return (0);
	ft_print(philo, "is sleeping");
	ft_sleep(philo->info->t_sleep);
	if (philo->finish == 1)
		return (0);
	ft_print(philo, "is thinking");
	return (1);
}

int	ft_eat(t_philo *philo)
{
	sem_wait(philo->lunch);
	philo->last_meal = ft_get_time();
	ft_print(philo, "is eating");
	sem_post(philo->lunch);
	ft_sleep(philo->info->t_eat);
	philo->nb_meals += 1;
	sem_post(philo->fork);
	sem_post(philo->fork);
	if (philo->finish == 1)
		return (0);
	return (1);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		ft_sleep(2);
	while (philo->finish == 0)
	{
		if (!ft_take_forks(philo))
			break ;
		if (!ft_eat(philo))
			break ;
		if (!ft_fall_asleep(philo))
			break ;
	}
	return (NULL);
}
