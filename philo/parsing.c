/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:54:12 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/10 19:03:51 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_msg(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int	ft_check_error(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] > '9' || av[i][j] < '0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_param(int ac, char **av, t_info *info)
{
	info->nb_philo = ft_atoi(av[1]);
	info->t_eat = ft_atoi(av[2]);
	info->t_sleep = ft_atoi(av[3]);
	info->t_die = ft_atoi(av[4]);
	if (ac == 6)
	{
		info->nb_eat = ft_atoi(av[5]);
		if (info->nb_eat <= 0)
			ft_print_msg("Invalid arguments");
	}
	if (info->nb_philo <= 0 || info->t_eat <= 0
		|| info->t_sleep <= 0 || info->t_die <= 0)
		ft_print_msg("Invalid arguments");
}
