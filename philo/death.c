/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:48:23 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/11 00:42:25 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	ft_unlock_forks(pthread_mutex_t *forks, unsigned int nb_philo)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < nb_philo)
// 		pthread_mutex_unlock(&forks[i++]);
// }

// int	ft_check_meals(t_philo *philo, t_info *info)
// {
// 	int	i;

// 	i = 0;
// 	while (i < info->nb_philo)
// 	{
// 		if (philo[i].nb_meals < info->nb_eat)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	ft_is_dead(t_philo *philo)
// {
// 	if (*philo->finish == 1)
// 		return (1);
// 	pthread_mutex_lock(&philo->lunch);
// 	if ((int)(ft_get_time() - philo->last_meal) >= philo->info->t_die)
// 	{
// 		pthread_mutex_unlock(&philo->lunch);
// 		if (*philo->finish == 0)
// 		{
// 			*philo->finish = 1;
// 			pthread_mutex_lock(philo->print);
// 			printf("%lums %zu died\n", ft_get_ts(philo->ts), philo->id);
// 			pthread_mutex_unlock(philo->print);
// 		}
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->lunch);
// 	return (0);
// }

// int	ft_check_die_of_philo(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philo->info->nb_eat)
// 	{
// 		if (ft_is_dead(&philo[i]))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_check_death(t_info *info, t_philo *philo, pthread_mutex_t *fork)
// {
// 	int	i;

// 	i = 0;
// 	while (*philo->finish == 0)
// 	{
// 		ft_sleep(4);
// 		ft_check_die_of_philo(philo);
// 		if (*philo->finish == 0 && info->nb_eat > 0
// 			&& ft_check_meals(philo, info))
// 		{
// 			*philo->finish = 1;
// 			ft_sleep(5);
// 			ft_print_msg("Everyone ate well ok");
// 		}
// 	}
// 	while (i < info->nb_philo)
// 	{
// 		if (i == 0 && *philo->finish == 1)
// 			ft_unlock_forks(fork, info->nb_philo);
// 		i++;
// 	}
// 	free(philo);
// 	join_philo(philo);
// 	return (1);
// }
//-------------------------------------------------------------------
void	unlock_forks(pthread_mutex_t *forks, unsigned int nb_philos)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
		pthread_mutex_unlock(&forks[i++]);
}

int	is_dead(t_philo *philo)
{
	if (*philo->finish == 1)
		return (1);
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
		return (1);
	}
	pthread_mutex_unlock(&philo->lunch);
	return (0);
}

int	check_meals(t_philo *philos, unsigned int nb_philos, long nb_meals)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
	{
		if (philos[i].nb_meals < nb_meals)
			return (0);
		i++;
	}
	return (1);
}

int	check_death(t_philo *philos, unsigned int nb_philos)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
	{
		if (is_dead(&philos[i]))
			return (1);
		i++;
	}
	return (0);
}

int	watch_threads(t_info *info, t_philo *philos, unsigned int nb_philos,
			pthread_mutex_t *forks)
{
	size_t	i;

	i = 0;
	while (*philos->finish == 0)
	{
		ft_sleep(4);
		check_death(philos, nb_philos);
		if (*philos->finish == 0 && info->nb_eat > 0
			&& check_meals(philos, nb_philos, info->nb_eat))
		{
			*philos->finish = 1;
			ft_sleep(5);
			printf("Everyone ate well\n");
		}
	}
	while (i < nb_philos)
	{
		if (i == 0 && *philos->finish == 1)
			unlock_forks(forks, nb_philos);
		if (pthread_join(philos[i].thread, NULL))
			return (0);
		i++;
	}
	free(philos);
	return (1);
}
