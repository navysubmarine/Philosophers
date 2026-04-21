/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:19:29 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/21 15:43:13 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		
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
		printf("Bonjour je suis le thread numero %d\n", philo->id);
		usleep(3000000);
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
	return (0);
}

static int	init(t_global *g, int argc, char **argv)
{
	if (init_struct(&g, argc, argv))
		return (1);
	if (init_philo(g, g->philo, g->nb_of_philo))
		return (1);
	if (init_threads(g, g->philo, g->nb_of_philo))
		return (1);
	return (0);
}

static int init_threads(t_global *g, t_philo **philo, unsigned int nb_of_philo)
{
	int i;

	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_create(&(philo[i]->th), NULL, &routine, philo[i]) != 0)
		{
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

	(void)g;
	i = 0;
	while (i < nb_of_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
		{
			//free_philos(philo, i);
			printf("Error: allocation failed\n");
			return (1);
		}
		memset(philo[i], 0, sizeof(t_philo));
		philo[i]->time_to_die = g->time_to_die;
		philo[i]->time_to_eat = g->time_to_eat;
		philo[i]->time_to_sleep = g->time_to_sleep;
		philo[i]->id = i;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_global	g;

	if (check_arg(argc, argv))
		return (1);
	if (init(&g, argc, argv))
		return (1);
	//if (init_threads())
	/*init threads
	join them
	lock
	access corresponding variables
	sleep for the time_to_eat time
	unlock the mutex
	*/
}
