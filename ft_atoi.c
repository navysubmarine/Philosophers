/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:39:05 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/28 14:26:56 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	signe(const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j++;
		i++;
	}
	if (j % 2 == 1)
	{
		return (-1);
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	reliquat;
	int	resultat;

	i = 0;
	reliquat = 0;
	resultat = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		resultat = resultat * 10;
		reliquat = nptr[i] - '0';
		if (signe(nptr) == 1)
			resultat = resultat + reliquat;
		else
			resultat = resultat - reliquat;
		i++;
	}
	return (resultat);
}