/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 15:36:55 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/28 15:37:50 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_solo_philo_thread(t_global *g, t_philo **philo)
{
	if (pthread_create(&(philo[0]->th), NULL, &routine_solo_philo,
			philo[0]) != 0)
	{
		free_global(g);
		printf("Error: thread creation failed\n");
		return (1);
	}
	return (0);
}

static int	init_several_philos_threads(t_global *g, t_philo **philo,
	unsigned int nb_of_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_create(&(philo[i]->th), NULL, &routine_philo,
				philo[i]) != 0)
		{
			free_global(g);
			printf("Error: thread creation failed\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	join_threads(t_global *g, t_philo **philo, unsigned int nb_of_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_join(philo[i]->th, NULL) != 0)
		{
			free_global(g);
			printf("Error: philo threads haven't been joined\n");
			return (1);
		}
		i++;
	}
	if (pthread_join(g->supervisor, NULL) != 0)
	{
		free_global(g);
		printf("Error: supervisor thread hasn't been joined\n");
		return (1);
	}
	return (0);
}

int	init_philo_threads(t_global *g, t_philo **philo, unsigned int nb_of_philo)
{
	pthread_mutex_lock(&(g->ok_init_mutex));
	if (nb_of_philo == 1)
	{
		if (init_solo_philo_thread(g, philo))
			return (1);
	}
	else
	{
		if (init_several_philos_threads(g, philo, nb_of_philo))
			return (1);
	}
	g->simulation_start = getcurrenttime();
	if (g->simulation_start < 0)
	{
		free_global(g);
		return (1);
	}
	pthread_mutex_unlock(&(g->ok_init_mutex));
	if (join_threads(g, philo, nb_of_philo))
		return (1);
	return (0);
}

int	init_supervisor_thread(t_global *g)
{
	if (pthread_create(&g->supervisor, NULL, &routine_supervisor, g) != 0)
	{
		free_global(g);
		printf("Error: supervisor thread creation failed\n");
		return (1);
	}
	return (0);
}
