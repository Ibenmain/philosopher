/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:48:23 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/10 19:38:40 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_meals(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (philo[i].nb_meals < info->nb_eat)
			return (0);
		i++;
	}
	return (1);
}

void	ft_check_die_of_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->nb_philo)
	{
		if (*philo->finish == 1)
			return ;
		pthread_mutex_lock(&philo->lunch);
		if ((int)(ft_get_time() - philo->last_meal) >= philo->info->t_die)
		{
			pthread_mutex_unlock(&philo->lunch);
			if (*philo->finish == 0)
			{
				*philo->finish = 1;
				pthread_mutex_lock(philo->print);
				printf("%lums %zu died\n", ft_get_ts(philo->ts), philo->id);
				pthread_mutex_unlock(philo->print);
			}
		}
	}
	pthread_mutex_unlock(&philo->lunch);
}

void	ft_check_death(t_info *info, t_philo *philo, pthread_mutex_t *fork)
{
	int	i;
	(void)fork;
	i = 0;
	while (*philo->finish == 0)
	{
		ft_sleep(5);
		ft_check_die_of_philo(philo);
		if (*philo->finish == 0 && ft_check_meals(philo, info))
		{
			*philo->finish = 1;
			ft_sleep(5);
			ft_print_msg("Everyone ate well ok");
		}
	}
	// ft_unlock_forks(philo, info);
	join_philo(philo);
	free(philo);
}
