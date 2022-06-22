/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:00:29 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/22 16:14:55 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	take_forks(t_philo *philo)
{
	if (*philo->stop == 1)
		return (0);
	sem_wait(philo->forks);
	if (*philo->stop == 1)
		return (0);
	ft_print(philo, "has taken a fork");
	sem_wait(philo->forks);
	if (*philo->stop == 1)
		return (0);
	ft_print(philo, "has taken a fork");
	return (1);
}

sem_t	*init_forks(t_info *info)
{
	sem_t	*forks;

	forks = ft_sem_init("print", info->nb_philo);
	return (forks);
}
