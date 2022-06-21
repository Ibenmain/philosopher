/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:16:12 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/21 13:18:12 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_children(t_philo *philos, unsigned int nb_philos)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
	{
		kill(philos[i].pid, SIGKILL);
		i++;
	}
	i = 0;
	while (i < nb_philos)
	{
		sem_close(philos[i].lunch);
		sem_unlink(philos[i].lunch_name);
		free(philos[i].lunch_name);
		i++;
	}
}

int	watch_children(t_philo *philos, unsigned int nb_philos)
{
	size_t	nb_full;
	int		status;

	nb_full = 0;
	while (philos->info->nb_eat > 0 && nb_full != nb_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != 1)
			break ;
		nb_full++;
	}
	if (philos->info->nb_eat < 0)
		waitpid(-1, &status, 0);
	kill_children(philos, nb_philos);
	if (philos->info->nb_eat && nb_full == nb_philos)
		printf("Everyone ate well\n");
	sem_close(philos->fork);
	sem_unlink("forks");
	sem_close(philos->sync);
	sem_unlink("sync");
	sem_post(philos->print);
	free(philos);
	return (1);
}
