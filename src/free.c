/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:06:06 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/28 12:08:19 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_philos(t_philo **philo, unsigned int nb)
{
	unsigned int	i;

	if (!philo)
		return ;
	i = 0;
	while (i < nb)
	{
		if (philo[i])
		{
			if (philo[i]->access_last_meal_time)
			{
				pthread_mutex_destroy(philo[i]->access_last_meal_time);
				free(philo[i]->access_last_meal_time);
			}
			free(philo[i]);
		}
		i++;
	}
	free(philo);
}

void	free_global(t_global *g)
{
	int	i;

	if (!g)
		return ;
	if (g->fork_mutex)
	{
		i = 0;
		while (i < g->nb_of_philo)
		{
			if (g->fork_mutex[i])
			{
				pthread_mutex_destroy(g->fork_mutex[i]);
				free(g->fork_mutex[i]);
			}
			i++;
		}
		free(g->fork_mutex);
		g->fork_mutex = NULL;
	}
	pthread_mutex_destroy(&g->ok_init_mutex);
	pthread_mutex_destroy(&g->access_stop_var_mutex);
	pthread_mutex_destroy(&g->access_print_messages);
	pthread_mutex_destroy(&g->access_philos_done);
	if (g->philo)
	{
		free_philos(g->philo, g->nb_of_philo);
		g->philo = NULL;
	}
}
