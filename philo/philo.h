/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:58:26 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/07 11:41:13 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_info
{
	int	nb_philo;
	int	t_eat;
	int	t_sleep;
	int	t_die;
	int	nb_eat;

}	t_info;

int		ft_atoi(char *str);
int		ft_cheak_error(char **av);
void	ft_param(int ac, char **av, t_info *info);
#endif