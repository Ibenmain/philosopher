/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 22:02:05 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/22 16:15:04 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	only_numbers(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

unsigned int	pars_nbr(char *str)
{
	size_t			i;
	unsigned int	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		nbr *= 10;
		nbr += str[i] - 48;
		i++;
	}
	return (nbr);
}

int	check_args(int argc, char **argv, t_info *pars)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) > 11 || !only_numbers(argv[i])
			|| (ft_strlen(argv[i]) == 11
				&& ft_strcmp(argv[i], "42949667295") > 0))
			return (0);
		i++;
	}
	pars->nb_philo = pars_nbr(argv[1]);
	pars->t_die = pars_nbr(argv[2]);
	pars->t_eat = pars_nbr(argv[3]);
	pars->t_sleep = pars_nbr(argv[4]);
	if (argc == 6)
		pars->nb_eat = pars_nbr(argv[5]);
	else
		pars->nb_eat = -1;
	if (!pars->nb_philo)
		return (0);
	return (1);
}
