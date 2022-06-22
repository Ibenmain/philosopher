/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:17:25 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/22 16:17:28 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*ft_sem_init(char *name, unsigned int val)
{
	sem_t	*semaphor;

	sem_unlink(name);
	semaphor = sem_open(name, O_CREAT, 0777, val);
	if (semaphor != SEM_FAILED)
		return (semaphor);
	sem_unlink(name);
	return (sem_open(name, O_CREAT, 0777, val));
}

int	main(int ac, char **av)
{
	t_info			info;
	sem_t			*print;
	int				ret;

	if (ac < 5 || ac > 6 || !check_args(ac, av, &info))
	{
		write(2, "Wrong arguments\n", 16);
		return (1);
	}
	if (!info.nb_eat)
	{
		printf("Everyone ate well, even though no one ate\n");
		return (0);
	}
	ret = 1;
	sem_unlink("print");
	print = ft_sem_init("print", 1);
	if (!launch_children(&info, print))
		ret = 0;
	sem_close(print);
	sem_unlink("print");
	return (ret);
}
