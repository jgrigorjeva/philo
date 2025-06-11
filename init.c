/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:00:36 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/10 22:59:12 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_table *table);

t_table	*init_all(t_input *input)
{
	t_table	*table;

	table = init_table(input);
	if (!table)
		return (NULL);
	init_philo_arr(table);
	table->start_time = get_time();
	if (init_mutex(table) || create_threads(table))
		return (NULL);
	return (table);
}

t_table	*init_table(t_input *input)
{
	t_table	*table;

	if (!input)
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table)
		return (printf("Error allocating table\n"), NULL);
	table->philo_nbr = input->philo_nbr;
	table->max_meals = input->meal_nbr;
	table->ttd = input->ttd;
	table->tte = input->tte;
	table->tts = input->tts;
	table->died_id = 0;
	table->philo_arr = malloc(sizeof(t_philo) * input->philo_nbr);
	if (!table->philo_arr)
		return (printf("Error allocating philo_arr\n"), NULL);
	table->fork_arr = malloc(sizeof(t_fork) * input->philo_nbr);
	if (!table->fork_arr)
		return (printf("Error allocating fork_arr\n"), NULL);
	return (table);
}

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

int	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->fork_arr[i].mutex, NULL) != 0)
			return (printf("Error in fork mutex initialization\n"), 1);
		i++;
	}
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (printf("Error in print_mutex initialization\n"), 1);
	if (pthread_mutex_init(&table->dead_mutex, NULL) != 0)
		return (printf("Error in dead_mutex initialization\n"), 1);
	return (0);
}

void	init_philo_arr(t_table *table)
{
	int	i;	

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philo_arr[i].id = i + 1;
		table->philo_arr[i].meals_eaten = 0;
		table->philo_arr[i].now_eating = FALSE;
		table->philo_arr[i].state = THINK;
		table->philo_arr[i].last_fed = 0;
		table->philo_arr[i].table = table;
		i++;
	}
	assign_forks(table);
}

int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_create(&table->monitor, NULL, &monitor_routine, &table))
		return (printf("Failed creating monitor thread\n"), 1);
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philo_arr[i].thread, \
			NULL, &routine, &table->philo_arr[i]))
			return (printf("Failed creating thread\n"), 1);
		i++;
	}
	return (0);
}