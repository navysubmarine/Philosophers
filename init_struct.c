/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:19:42 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/28 18:49:54 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo_fields(t_global *g, t_philo *philo, unsigned int i)
{
	memset(philo, 0, sizeof(t_philo));
	philo->time_to_die = g->time_to_die;
	philo->time_to_eat = g->time_to_eat;
	philo->time_to_sleep = g->time_to_sleep;
	philo->id = i + 1;
	philo->g = g;
}

static void	init_philo_forks(t_global *g, t_philo *philo,
				unsigned int i, unsigned int nb_of_philo)
{
	philo->right_fork = g->fork_mutex[i];
	if (i == 0)
		philo->left_fork = g->fork_mutex[nb_of_philo - 1];
	else
		philo->left_fork = g->fork_mutex[i - 1];
}

static int	init_one_philo(t_global *g, t_philo **philo,
				unsigned int i, unsigned int nb_of_philo)
{
	int	ret;

	philo[i] = malloc(sizeof(t_philo));
	if (!philo[i])
	{
		printf("Error: philo allocation failed\n");
		return (1);
	}
	init_philo_fields(g, philo[i], i);
	init_philo_forks(g, philo[i], i, nb_of_philo);
	ret = init_meal_mutex(philo[i]);
	return (ret);
}

int	init_philo_struct(t_global *g, t_philo **philo, unsigned int nb_of_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nb_of_philo)
	{
		if (init_one_philo(g, philo, i, nb_of_philo))
			return (1);
		i++;
	}
	return (0);
}

int	init_g_struct(t_global *g, int argc, char **argv)
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
	if (init_g_mutex(g, g->fork_mutex, g->nb_of_philo))
		return (1);
	return (0);
}
