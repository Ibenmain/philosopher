/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:47:18 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/21 13:01:42 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_info			*info;
	t_philo			*philo;
	sem_t			*print;
	sem_t			*forks;

	if ((argc != 5 && argc != 6) || ft_check_error(argv))
		return (printf("Invalid arguments"), 0);
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	info = malloc(sizeof(t_info) * ft_atoi(argv[1]));
	if (!philo || !info)
		return (0);
	ft_param(argc, argv, info);
	forks = ft_sem_init("forks", info->nb_philo);
	print = ft_sem_init("print", 1);
	launch_children(philo, info, forks, print);
	sem_close(print);
	sem_unlink("print");
	return (0);
}
