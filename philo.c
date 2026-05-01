/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:19:29 by marthoma          #+#    #+#             */
/*   Updated: 2026/05/01 10:50:44 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_global *g, int argc, char **argv)
{
	if (init_g_struct(g, argc, argv))
	{
		free_global(g);
		return (1);
	}
	if (init_philo_struct(g, g->philo, g->nb_of_philo))
	{
		free_global(g);
		return (1);
	}
	if (init_threads(g, g->philo, g->nb_of_philo))
	{
		free_global(g);
		return (1);
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
	free_global(&g);
	return (0);
}
