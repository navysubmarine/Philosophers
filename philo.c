/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:19:29 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/22 15:35:03 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_philo			*philo;
	//struct timeval	start;
	int				i;

	i = 0;
	philo = (t_philo *)data;
	// if (gettimeofday(&start, NULL))
	// 	return (NULL);
	while (1)
	{
		//pthread_mutex_lock(philo->g->mutex);
		//printf("start= %d\n", (int)start->tv_sec);
		printf("ID: %d - I am eating\n", philo->id);
		usleep(philo->time_to_eat * 1000);
		//pthread_mutex_unlock(philo->g->mutex);
		printf("ID: %d - I am sleeping\n", philo->id);
		usleep(philo->time_to_sleep * 1000);
		printf("ID: %d - I am thinking\n", philo->id);
		/*eat, sleep and think
		first try to access the variable
		if it has been locked, wait until it's unlocked
		escape the loop when the time_to_die is smaller than
		the time since the last time you ate
		lock it
		eat = print "is_eating"
		start counting and
		escape when time_to_eat is over
		unlock it
		start counting last_time_you_ate
		sleep for the time_to_sleep amount
		then think for the time_to_think amount
		then repeat
		*/
		//printf("Bonjour je suis le thread numero %d\n", philo->id);
		i++;
	}
	return (NULL);
}

static int	init_struct(t_global *g, int argc, char **argv)
{
	memset(g, 0, sizeof(t_global));
	g->nb_of_philo = ft_atoi(argv[1]);
	g->time_to_die = ft_atoi(argv[2]);
	g->time_to_eat = ft_atoi(argv[3]);
	g->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		g->nb_eat = ft_atoi(argv[5]);
	else
		g->nb_eat = -1;
	g->philo = malloc(sizeof(t_philo *) * g->nb_of_philo);
	if (!g->philo)
		return (1);
	g->mutex = malloc(sizeof(pthread_mutex_t *) * g->nb_of_philo);
	if (!g->mutex)
		return (free(g->philo), 1);
	return (0);
}

static int	init_threads(t_global *g, t_philo **philo, unsigned int nb_of_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_create(&(philo[i]->th), NULL, &routine, philo[i]) != 0)
		{
			free_global(g);
			printf("Error: thread creation failed\n");
			return (1);
		}
		printf("Thread %d a ete cree\n", i);
		i++;
	}
	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_join(philo[i]->th, NULL) != 0)
		{
			free_global(g);
			printf("Error: thread haven't been joined\n");
			return (1);
		}
		printf("Thread %d has finished execution\n", i);
		i++;
	}
	return (0);
}

static int	init_philo(t_global *g, t_philo **philo, unsigned int nb_of_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nb_of_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
		{
			free_global(g);
			printf("Error: philo allocation failed\n");
			return (1);
		}
		memset(philo[i], 0, sizeof(t_philo));
		philo[i]->time_to_die = g->time_to_die;
		philo[i]->time_to_eat = g->time_to_eat;
		philo[i]->time_to_sleep = g->time_to_sleep;
		philo[i]->id = i;
		philo[i]->g = g;
		philo[i]->right_fork = g->mutex[i];
		if (i == 0)
			philo[i]->left_fork = g->mutex[nb_of_philo - 1];
		else
			philo[i]->left_fork = g->mutex[i - 1];
		i++;
	}
	return (0);
}

static int	init_mutex(t_global *g, pthread_mutex_t **mutex, unsigned int nb_of_philo)
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
		pthread_mutex_init(mutex[i], NULL);
		i++;
	}
	return (0);
}

static int	init(t_global *g, int argc, char **argv)
{
	if (init_struct(g, argc, argv))
		return (1);
	if (init_mutex(g, g->mutex, g->nb_of_philo))
		return (1);
	if (init_philo(g, g->philo, g->nb_of_philo))
		return (1);
	if (init_threads(g, g->philo, g->nb_of_philo))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_global	g;

	if (check_arg(argc, argv))
		return (1);
	if (init(&g, argc, argv))
		return (1);
}
