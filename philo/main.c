/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:47:18 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/11 17:16:59 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info			info;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;

	if ((argc != 5 && argc != 6) || ft_check_error(argv))
		return (printf("Invalid arguments"), 0);
	ft_param(argc, argv, &info);
	forks = ft_creat_fork(&info);
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return (0);
	pthread_mutex_init(&print, NULL);
	if (ft_start_lunch(philo, &info, forks, &print))
		return (1);
	destroy_forks(forks, &info);
	pthread_mutex_destroy(&print);
	return (0);
}
