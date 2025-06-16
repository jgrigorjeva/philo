/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:44:14 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/16 18:44:35 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philo_arr[i].right_fork = &table->fork_arr[i];
		table->philo_arr[i].left_fork \
		= &table->fork_arr[(i + 1) % table->philo_nbr];
		table->fork_arr[i].stat = -1;
		i++;
	}
}
