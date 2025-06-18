/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:36:27 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/18 19:57:29 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_death(t_table *table, int i);

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;
	long	now;
	long	timestamp;

	table = (t_table *)arg;
	wait_before_start(table);
	while (!is_dead(table))
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			now = get_time();
			timestamp = now - table->start_time;
			if (should_die(timestamp, &table->philo_arr[i]))
			{
				handle_death(table, i);
				return (NULL);
			}
			i++;
		}
		ft_msleep(1);
	}
	return (NULL);
}

void	handle_death(t_table *table, int i)
{
	pthread_mutex_lock(&table->dead_mutex);
	table->someone_died = TRUE;
	pthread_mutex_unlock(&table->dead_mutex);
	if (!all_meals_eaten(table))
		print_status(&table->philo_arr[i], "died");
}
