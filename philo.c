/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:19:29 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/27 15:42:50 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_global *g, t_philo **philo, unsigned int nb_of_philo)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&(g->ok_init_mutex));
	if (nb_of_philo == 1)
	{
		if (pthread_create(&(philo[0]->th), NULL, &routine_solo_philo,
				philo[0]) != 0)
		{
			free_global(g);
			printf("Error: thread creation failed\n");
			return (1);
		}
	}
	else
	{
		while (i < nb_of_philo)
		{
			if (pthread_create(&(philo[i]->th), NULL, &routine_philo,
					philo[i]) != 0)
			{
				free_global(g);
				printf("Error: thread creation failed\n");
				return (1);
			}
			// printf("Thread %d a ete cree\n", i + 1);
			i++;
		}
	}
	g->simulation_start = getcurrenttime();
	if (g->simulation_start < 0)
	{
		free_global(g);
		return (1);
	}
	pthread_mutex_unlock(&(g->ok_init_mutex));
	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_join(philo[i]->th, NULL) != 0)
		{
			free_global(g);
			printf("Error: philo threads haven't been joined\n");
			return (1);
		}
		// printf("Thread %d has finished execution\n", i + 1);
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

int	init_supervisor(t_global *g)
{
	if (pthread_create(&g->supervisor, NULL, &routine_supervisor, g) != 0)
	{
		free_global(g);
		printf("Error: supervisor thread creation failed\n");
		return (1);
	}
	// printf("Supervisor a ete cree\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_global	g;

	if (check_arg(argc, argv))
		return (1);
	if (init(&g, argc, argv))
		return (1);
	free_global(&g);
	return (0);
}
