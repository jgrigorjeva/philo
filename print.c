/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:37:17 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/10 23:34:03 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, const char *msg)
{
	t_table	*table;
	long	now;
	long	timestamp;

	table = philo->table;
	now = get_time();
	timestamp = now - table->start_time;
	pthread_mutex_lock(&table->print_mutex);
	printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&table->print_mutex);
}