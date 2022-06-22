/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:15:17 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/22 16:15:21 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_bonus.h"

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
