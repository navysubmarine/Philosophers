/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:19:42 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/23 19:04:11 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_philo(t_global *g, t_philo **philo, unsigned int nb_of_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nb_of_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
		{
			printf("Error: philo allocation failed\n");
			return (1);
		}
		memset(philo[i], 0, sizeof(t_philo));
		philo[i]->time_to_die = g->time_to_die;
		philo[i]->time_to_eat = g->time_to_eat;
		philo[i]->time_to_sleep = g->time_to_sleep;
		philo[i]->id = i + 1;
		philo[i]->g = g;
		philo[i]->right_fork = g->fork_mutex[i];
		if (i == 0)
			philo[i]->left_fork = g->fork_mutex[nb_of_philo - 1];
		else
			philo[i]->left_fork = g->fork_mutex[i - 1];
		philo[i]->end = 0;
		philo[i]->start = 0;
		i++;
	}
	return (0);
}

int	init_mutex(t_global *g, pthread_mutex_t **mutex, unsigned int nb_of_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nb_of_philo)
	{
		mutex[i] = malloc(sizeof(pthread_mutex_t));
		if (!mutex[i])
		{
			free_global(g);
			printf("Error: mutex allocation failed\n");
			return (1);
		}
		if (pthread_mutex_init(mutex[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(g->ok_init_mutex, NULL))
		return (1);
	return (0);
}

int	init_struct(t_global *g, int argc, char **argv)
{
	memset(g, 0, sizeof(t_global));
	g->nb_of_philo = ft_atoi(argv[1]);
	g->time_to_die = ft_atoi(argv[2]);
	g->time_to_eat = ft_atoi(argv[3]);
	g->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		g->max_eat = ft_atoi(argv[5]);
	else
		g->max_eat = -1;
	
	g->philo = malloc(sizeof(t_philo *) * g->nb_of_philo);
	if (!g->philo)
		return (1);
	memset(g->philo, 0, sizeof(t_philo *) * g->nb_of_philo);
	
	g->fork_mutex = malloc(sizeof(pthread_mutex_t *) * g->nb_of_philo);
	if (!g->fork_mutex)
		return (free(g->philo), 1);
	memset(g->fork_mutex, 0, sizeof(pthread_mutex_t *) * g->nb_of_philo);
	
	g->ok_init_mutex = malloc(sizeof(pthread_mutex_t));
	if (!g->ok_init_mutex)
		return (free(g->philo), free(g->fork_mutex), 1);

	g->access_stop_var_mutex = malloc(sizeof(pthread_mutex_t));
	if (!g->access_stop_var_mutex)
		return (free(g->philo), free(g->fork_mutex), free(g->ok_init_mutex), 1);

	return (0);
}

int	init(t_global *g, int argc, char **argv)
{
	if (init_struct(g, argc, argv))
	{
		free_global(g);
		return (1);
	}
	if (init_mutex(g, g->fork_mutex, g->nb_of_philo))
	{
		free_global(g);
		return (1);
	}
	if (init_philo(g, g->philo, g->nb_of_philo))
	{
		free_global(g);
		return (1);
	}
	if (init_supervisor(g))
	{
		free_global(g);
		return (1);
	}
	//print_global(g);
	if (init_threads(g, g->philo, g->nb_of_philo))
	{
		free_global(g);
		return (1);
	}
	return (0);
}
