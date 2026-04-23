/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:19:29 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/23 16:03:30 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	getcurrenttime(void)
{
	struct timeval	time;
	long			value;

	if (gettimeofday(&time, NULL))
		return (0);
	else
	{
		value = (long)time.tv_sec * 1000 + (long)time.tv_usec / 1000;
		return (value);
	}
}

int	think(t_philo *philo)
{
	if(philo->g->stop)
		return (1);
	printf("%sID: %d - I am thinking%s\n", GREEN, philo->id, NC);
	return (0);
}

int	eat(t_philo *philo)
{
	if (philo->g->stop)
		return (1);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	philo->end = getcurrenttime();
	if (!philo->end)
		return (1);
	if (philo->g->stop)
		return (1);
	printf("%sID: %d - I am eating%s\n", YELLOW, philo->id, NC);
	philo->start = getcurrenttime();
	if (!philo->start)
		return (1);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (philo->g->stop)
		return (1);
	return (0);
}

int	my_sleep(t_philo *philo)
{
	if (philo->g->stop)
		return (1);
	printf("%sID: %d - I am sleeping%s\n", BLUE, philo->id, NC);
	usleep(philo->time_to_sleep * 1000);
	return (0);
}

void	*routine_philo(void *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)data;
	pthread_mutex_lock(philo->g->ok_init_mutex);
	pthread_mutex_unlock(philo->g->ok_init_mutex);
	philo->end = getcurrenttime();
	if (!philo->end)
		return (NULL);
	philo->start = philo->end;
	if (philo->g->stop)
		return (NULL);
	while (1)
	{
		think(philo);
		if (eat(philo))
			return (NULL);
		my_sleep(philo);
		i++;
	}
	return (NULL);
}

void	*routine_supervisor(void *data)
{
	unsigned int i;
	t_global *g;

	i = 0;
	g = (t_global *)data;
	while (1)
	{
		while (i < g->nb_of_philo)
		{
			if((g->philo[i]->end - g->philo[i]->start) > g->time_to_die)
			{
				g->stop = 1;
				printf("%sPhilo %d is dead %s\n", PURPLE, g->philo[i]->id, NC);
				return (NULL);
			}	
			i++;
		}
		i = 0;
	}
	return (NULL);
}


int	init_struct(t_global *g, int argc, char **argv)
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
	g->fork_mutex = malloc(sizeof(pthread_mutex_t *) * g->nb_of_philo);
	if (!g->fork_mutex)
		return (free(g->philo), 1);
	g->ok_init_mutex = malloc(sizeof(pthread_mutex_t));
	if (!g->ok_init_mutex)
		return (free(g->philo), free(g->fork_mutex), 1);
	g->supervisor = malloc(sizeof(pthread_t));
	if (!g->supervisor)
		return (free(g->philo), free(g->fork_mutex), free(g->ok_init_mutex), 1);
	return (0);
}

int	init_threads(t_global *g, t_philo **philo, unsigned int nb_of_philo)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(g->ok_init_mutex);
	while (i < nb_of_philo)
	{
		if (pthread_create(&(philo[i]->th), NULL, &routine_philo, philo[i]) != 0)
		{
			free_global(g);
			printf("Error: thread creation failed\n");
			return (1);
		}
		printf("Thread %d a ete cree\n", i + 1);
		i++;
	}
	pthread_mutex_unlock(g->ok_init_mutex);
	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_join(philo[i]->th, NULL) != 0)
		{
			free_global(g);
			printf("Error: thread haven't been joined\n");
			return (1);
		}
		printf("Thread %d has finished execution\n", i + 1);
		i++;
	}
	return (0);
}

int	init_philo(t_global *g, t_philo **philo, unsigned int nb_of_philo)
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

int	init_supervisor(t_global *g)
{
	if (pthread_create(g->supervisor, NULL, &routine_supervisor, g) != 0)
	{
		free_global(g);
		printf("Error: supervisor thread creation failed\n");
		return (1);
	}
	printf("Supervisor a ete cree\n");
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
		pthread_mutex_init(mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(g->ok_init_mutex, NULL);
	return (0);
}

static int	init(t_global *g, int argc, char **argv)
{
	if (init_struct(g, argc, argv))
		return (1);
	if (init_mutex(g, g->fork_mutex, g->nb_of_philo))
		return (1);
	if (init_philo(g, g->philo, g->nb_of_philo))
		return (1);
	if (init_supervisor(g))
	 	return (1);
	print_global(g);
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
