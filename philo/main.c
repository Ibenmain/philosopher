/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:47:18 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/08 21:44:02 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info			info;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;

	if ((argc != 5 && argc != 6) || ft_cheak_error(argv))
		return (printf("Invalid arguments"), 0);
	ft_param(argc, argv, &info);
	forks = ft_creat_fork(&info);
	pthread_mutex_init(&print, NULL);
	ft_start_lunch(&info, forks, &print);
	join_philo(&info);
}
