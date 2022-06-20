/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:48:05 by ibenmain          #+#    #+#             */
/*   Updated: 2022/06/20 14:10:36 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_nbr(long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	if (n == 0)
		count++;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char	*ft_other_itoa(long int k, int size)
{
	char	*chain;

	chain = (char *)malloc(size + 1 * sizeof(char));
	if (!chain)
		return (NULL);
	chain[size--] = '\0';
	if (k < 0)
	{
		k *= -1;
		chain[0] = '-';
		while (size > 0)
		{
			chain[size--] = k % 10 + '0';
			k = k / 10;
		}
	}
	else
	{
		while (size >= 0)
		{
			chain[size--] = k % 10 + '0';
			k = k / 10;
		}
	}
	return (chain);
}

char	*ft_itoa(int n)
{
	char		*chain;
	int			size;
	long int	k;

	k = n;
	size = ft_nbr(k);
	chain = ft_other_itoa(k, size);
	return (chain);
}

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	size_s1;
	size_t	size_s2;
	char	*new;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	new = (char *)malloc((size_s1 + size_s2) + 1 * sizeof(char));
	if (!new)
		return (NULL);
	while (i < size_s1)
	{
		new[i] = s1[i];
		i++;
	}
	while (j < size_s2)
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

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
