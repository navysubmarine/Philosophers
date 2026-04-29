/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:46:59 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/29 22:35:45 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_g_mutex(t_global *g, pthread_mutex_t **fork_mutex,
	unsigned int nb_of_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nb_of_philo)
	{
		fork_mutex[i] = malloc(sizeof(pthread_mutex_t));
		if (!fork_mutex[i])
		{
			free_global(g);
			printf("Error: mutex allocation failed\n");
			return (1);
		}
		if (pthread_mutex_init(fork_mutex[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(g->ok_init_mutex), NULL))
		return (1);
	if (pthread_mutex_init(&(g->access_stop_var_mutex), NULL))
		return (1);
	if (pthread_mutex_init(&(g->access_print_messages), NULL))
		return (1);
	if (pthread_mutex_init(&(g->access_philos_done), NULL))
		return (1);
	return (0);
}

int	init_meal_mutex(t_philo *philo)
{
	philo->access_last_meal_time = malloc(sizeof(pthread_mutex_t));
	if (!philo->access_last_meal_time)
		return (1);
	if (pthread_mutex_init(philo->access_last_meal_time, NULL))
		return (1);
	return (0);
}
