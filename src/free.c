/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:06:06 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/21 15:06:30 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_philos(t_philo **philo, unsigned int nb)
{
	unsigned int	i;

	i = 0;
	while (i < nb)
		free(philo[i++]);
	free(philo);
}
