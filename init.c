/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:00:36 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/31 20:22:51 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*init_table(t_input *input)
{
	t_table	*table;

	if (!input)
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table)
		return (printf("Error allocating table\n"), NULL);
	table->philo_nbr = input->philo_nbr;
	table->philo_arr = malloc(sizeof(t_philo) * input->philo_nbr);
	if (!table->philo_arr)
		return (printf("Error allocating philo_arr\n"), NULL);
	table->fork_arr = malloc(sizeof(t_fork) * input->philo_nbr);
	if (!table->fork_arr)
		return (printf("Error allocating fork_arr\n"), NULL);
	return (table);
}

void	assign_id_and_forks(t_table *table)
{
	int	i;
	
	i = 0;
	while (i < table->philo_nbr)
	{
		table->philo_arr[i].id = i + 1;
		table->philo_arr[i].right_fork = &table->fork_arr[i];
		table->philo_arr[i].left_fork = &table->fork_arr[(i + 1) % table->philo_nbr];
		i++;
	}
}