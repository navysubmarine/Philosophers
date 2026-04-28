/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:41:13 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/28 15:20:28 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	getcurrenttime(void)
{
	struct timeval	time;
	long			value;

	if (gettimeofday(&time, NULL))
		return (-1);
	else
	{
		value = (long)time.tv_sec * 1000 + (long)time.tv_usec / 1000;
		return (value);
	}
}
