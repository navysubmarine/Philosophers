/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:31:58 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/23 14:28:25 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_philo(t_philo *philo)
{
	printf("  [Philo %u]\n", philo->id);
	printf("    id              : %u\n", philo->id);
	printf("    start		    : %ld\n", philo->start);
	printf("    end			    : %ld\n", philo->end);	
	printf("    time_to_die     : %u\n", philo->time_to_die);
	printf("    time_to_eat     : %u\n", philo->time_to_eat);
	printf("    time_to_sleep   : %u\n", philo->time_to_sleep);
	printf("    left_fork  ptr  : %p\n", (void *)philo->left_fork);
	printf("    right_fork  ptr : %p\n", (void *)philo->right_fork);
	printf("    g ptr           : %p\n", (void *)philo->g);
}

void	print_global(t_global *g)
{
	unsigned int i;

	printf("=== t_global ===\n");
	printf("  fork_mutex[1]: %p\n", g->fork_mutex[0]);
	printf("  fork_mutex[2]: %p\n", g->fork_mutex[1]);
	printf("  fork_mutex[3]: %p\n", g->fork_mutex[2]);
	printf("  fork_mutex[4]: %p\n", g->fork_mutex[3]);
	printf("  nb_of_philo  : %u\n", g->nb_of_philo);
	printf("  time_to_die  : %u\n", g->time_to_die);
	printf("  time_to_eat  : %u\n", g->time_to_eat);
	printf("  time_to_sleep: %u\n", g->time_to_sleep);
	printf("  nb_eat       : %d\n", g->nb_eat);
	printf("  mutex ptr    : %p\n", (void *)g->fork_mutex);
	printf("  philo ptr    : %p\n", (void *)g->philo);
	printf("\n=== Philosophers ===\n");
	i = 0;
	while (i < g->nb_of_philo)
	{
		if (g->philo[i])
			print_philo(g->philo[i]);
		else
			printf("  [Philo %u] NULL\n", i);
		i++;
	}
}