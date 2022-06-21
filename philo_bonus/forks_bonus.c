/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:00:29 by aanjaimi          #+#    #+#             */
/*   Updated: 2022/06/21 22:54:49 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	take_forks(t_philo *philo)
{
	if (*philo->stop == true)
		return (0);
	sem_wait(philo->forks);
	if (*philo->stop == true)
		return (0);
	ft_print(philo, "has taken a fork");
	sem_wait(philo->forks);
	if (*philo->stop == true)
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
