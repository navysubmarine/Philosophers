/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:04:19 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/22 14:28:36 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_valid_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		return (0);
	while (arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] >= '0' && arg[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_arg(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("Error: expected format: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (argv[i][0] == '\0')
		return (1);
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			printf("Error: arguments must be positive numbers\n");
			return (1);
		}
		i++;
	}
	if (ft_atoi(argv[1]) < 1)
	{
		printf("Error: there must be at least one philosopher\n");
		return (1);
	}
	return (0);
}
