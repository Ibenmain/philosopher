/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:10:47 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/21 13:22:22 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_unlock_sync(sem_t *sync, unsigned int nb_philos)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
	{
		sem_post(sync);
		i++;
	}
}

int	is_dead(t_philo *philo)
{
	if (philo->finish == 1)
		return (1);
	sem_wait(philo->lunch);
	if (ft_get_time() - philo->last_meal >= (unsigned int)philo->info->t_die)
	{
		sem_post(philo->lunch);
		if (philo->finish == 0)
		{
			philo->finish = 1;
			sem_wait(philo->print);
			printf("%lums %zu died\n", ft_get_ts(philo->ts), philo->id);
		}
		return (1);
	}
	sem_post(philo->lunch);
	return (0);
}
