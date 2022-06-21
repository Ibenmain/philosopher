/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:00:16 by aanjaimi          #+#    #+#             */
/*   Updated: 2022/06/21 22:14:35 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(char *str)
{
	int			i;
	int			signe;
	long int	nb;

	i = 0;
	signe = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		signe = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] != '\0') && (str[i] >= '0') && (str[i] <= '9'))
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	if (signe == -1)
		return (signe * nb);
	else
		return (nb);
}

static unsigned int	get_len(unsigned int nb, unsigned int *pow)
{
	unsigned int	len;

	len = 1;
	*pow = 1;
	while (*pow <= nb / 10)
	{
		*pow *= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t			i;
	unsigned int	pow;
	unsigned int	nb;
	static char		*base = "0123456789";
	char			*word;

	i = n < 0;
	if (n < 0)
		nb = n;
	else
		nb = -n;
	word = malloc(sizeof(char) * (get_len(nb, &pow) + i + 1));
	if (!word)
		return (0);
	if (n < 0)
		word[0] = '-';
	while (pow >= 1)
	{
		word[i] = base[nb / pow];
		nb -= pow * (nb / pow);
		pow /= 10;
		i++;
	}
	word[i] = 0;
	return (word);
}
