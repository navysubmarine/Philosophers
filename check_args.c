/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:04:19 by marthoma          #+#    #+#             */
/*   Updated: 2026/05/04 15:00:07 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static int	is_not_int(char **argv)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (ft_atoi(argv[i]) > 2147483647)
			return (1);
		i++;
	}
	if (argv[5])
	{
		if (ft_atoi(argv[5]) > 2147483647)
			return (1);
	}
	return (0);
}

static int	check_conditions(char **argv)
{
	if (is_not_int(argv))
	{
		printf("Error: all arguments must not be bigger than");
		printf("the size of an integer\n");
		return (1);
	}
	if (ft_atoi(argv[1]) < 1)
	{
		printf("Error: there must be at least one philosopher\n");
		return (1);
	}
	if (ft_atoi(argv[1]) > 200)
	{
		printf("Error: do not test with more than 200 philosophers\n");
		return (1);
	}
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
	{
		printf("Error: do not test with time set to values lower than 60ms\n");
		return (1);
	}
	return (0);
}

int	check_arg(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("Error: expected format: ./philo number_of_philosophers ");
		printf("time_to_die time_to_eat time_to_sleep [number_of_times_");
		printf("each_philosopher_must_eat]\n");
		return (1);
	}
	while (i < argc)
	{
		if (argv[i][0] == '\0' || !is_valid_number(argv[i]))
		{
			printf("Error: arguments must be positive numbers\n");
			return (1);
		}
		i++;
	}
	if (check_conditions(argv))
		return (1);
	return (0);
}
