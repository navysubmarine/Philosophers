/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:06:06 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/24 18:23:42 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    free_philos(t_philo **philo, unsigned int nb)
{
    unsigned int    i;

    if (!philo)
        return ;
    i = 0;
    while (i < nb)
    {
        if (philo[i])
            free(philo[i]);
        i++;
    }
    free(philo);
}

void    free_global(t_global *g)
{
    int    i;

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
    }
    if (g->philo)
        free_philos(g->philo, g->nb_of_philo);
}
